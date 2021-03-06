/// Program for interfacing with the SAM-BA bootloader on a SAM3X8E
/// microcontroller via USB.
///
/// Several comments refer the the SAM3X/SAM3A data sheet, available at the
/// following URI:
/// http://www.atmel.com/Images/Atmel-11057-32-bit-Cortex-M3-Microcontroller-SAM3X-SAM3A_Datasheet.pdf


mod eefc;
mod result;
mod sam_ba;
mod serial_port;
mod utils;


extern crate byteorder;
extern crate serial;


use std::env;
use std::fs::File;

use byteorder::{
    LittleEndian,
    ReadBytesExt,
};

use eefc::{
    Eefc,
    ErasePageAndWritePage,
    GpnvmNumber,
    Page,
    SetGpnvmBit,
};
use sam_ba::SamBa;


fn main() {
    let mut args = env::args();
    args.next().expect("Expected program name as first entry in args");

    let device_path = args.next().expect("Expected device path argument");
    let command     = args.next().expect("Expected command argument");

    let port = serial_port::init(&device_path)
        .expect("Failed to initialize serial port");

    let mut sam_ba = SamBa::new(port);
    let     eefc_0 = Eefc::eefc_0();

    sam_ba.set_normal_mode().expect("Failed to set normal mode");

    match command.as_ref() {
        "version" => {
            let version = sam_ba.display_version()
                .expect("Failed to retrieve version");

            print!("{}", version)
        },

        "upload-file" => {
            let path = args.next().expect("Expected file path argument");

            let mut file = File::open(&path).expect("Failed to create file");

            let file_size = file
                .metadata()
                .expect("Failed to read file metadata")
                .len();

            if file_size > 256 * 1024 {
                // The SAM3X8E has 512 KiB of memory, but it is divided into
                // two planes of 256 KiB each. The code below doesn't really
                // take that into account and would silently fail in various
                // ways, if the file were bigger than 256 KiB.
                // See sections 7.2.3 and chapter 18 in the data sheet for more
                // information.
                panic!("{} {}",
                    "The file is too big. This program only supports file",
                    "sizes up to 256 KiB."
                );
            }

            // Given the check above, we know that the following cast is safe.
            let file_size = file_size as u32;

            // Base address of the internal flash memory. See data sheet,
            // section 7.1.
            let flash_base_addr = 0x00080000;

            // Pages consist of 256 bytes each. A word is 4 bytes long, as ARM
            // is a 32-bit architecture.
            // See sections 7.2.3.1 and 10.4.5 in the data sheet.
            let word_size_bytes = 4;
            let page_size_bytes = 256;
            let page_size_words = page_size_bytes / word_size_bytes;

            let number_of_pages =
                (file_size + page_size_bytes - 1) / page_size_bytes;

            // This sets the number of wait states for flash read/write
            // operations to 6. See data sheet, section 18.5.1. According to
            // the errata section, this is required. Otherwise data written can
            // be corrupted. See section 49.1.1.1.
            // Please note that I wasn't able to verify that this really is
            // necessary. However, I was testing with a binary that wasn't
            // optimized. It is probable that flipping some bits here or there
            // wouldn't inhibit the functioning of that binary.
            sam_ba.write_word(0x400E0A00, 0x00000600)
                .expect("Failed to write wait state");

            for page in 0 .. number_of_pages {
                for i in 0 .. page_size_words {
                    let offset  = page * page_size_bytes + i * word_size_bytes;
                    let address = flash_base_addr + offset;

                    let word = if offset < file_size {
                        file.read_u32::<LittleEndian>()
                            .expect("Failed to read from file")
                    }
                    else {
                        0
                    };

                    sam_ba.write_word(address, word)
                        .expect("Failed to write word");
                }

                eefc_0
                    .execute_command::<ErasePageAndWritePage, _>(
                        &mut sam_ba,
                        Page(page as u16),
                    )
                    .expect("Failed erase page and write page");
            }

            eefc_0
                .execute_command::<SetGpnvmBit, _>(
                    &mut sam_ba,
                    GpnvmNumber::BootModeSelection,
                )
                .expect("Failed to set GPNVM bit");

            print!(
                "Wrote {} bytes ({} pages)\n",
                file_size, number_of_pages,
            );
        },

        _ =>
            print!("Unknown command: {}\n", command),
    }
}
