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

use eefc::{
	Eefc,
	GetGpnvmBit,
	GpnvmNumber,
	SetGpnvmBit,
};
use sam_ba::SamBa;


fn main() {
	let mut args = env::args();
	args.next().unwrap();

	let device_path = args.next().unwrap();
	let command     = args.next().unwrap();

	let     port   = serial_port::init(&device_path).unwrap();
	let mut sam_ba = SamBa::new(port);
	let     eefc_0 = Eefc::eefc_0();

	sam_ba.set_normal_mode().unwrap();

	match command.as_ref() {
		"version" =>
			print!("{}", sam_ba.display_version().unwrap()),
		"boot-mode" => {
			let result =
				eefc_0.execute_command::<GetGpnvmBit, _>(
					&mut sam_ba,
					GpnvmNumber::BootModeSelection,
				)
				.unwrap();

			print!("{:0>8x}\n", result)
		},
		"boot-from-flash" => {
			eefc_0.execute_command::<SetGpnvmBit, _>(
				&mut sam_ba,
				GpnvmNumber::BootModeSelection,
			)
			.unwrap();
		},
		_ =>
			print!("Unknown command: {}\n", command),
	}
}