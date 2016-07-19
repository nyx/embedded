use serial;
use serial::prelude::*;
use std::time::Duration;

pub fn init(path: &str) -> serial::Result<serial::SystemPort> {
    let mut port = try!(serial::open(path));
    try!(port.set_timeout(Duration::from_millis(2000)));

    try!(port.reconfigure(&|settings| {
        try!(settings.set_baud_rate(serial::Baud115200));
        settings.set_char_size(serial::Bits8);
        settings.set_parity(serial::ParityNone);
        settings.set_stop_bits(serial::Stop1);
        Ok(())
    }));

    Ok(port)
}
