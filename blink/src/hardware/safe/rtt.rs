use core::num::Wrapping;

use hardware::base::rtt::RTT;
use hardware::safe::nvic::Nvic;


pub struct Timer(());

impl Timer {
    /// Create an interface to the timer hardware.
    ///
    /// This constructor is marked unsafe, as it returns an instance that serves
    /// as an interface to something fundamentally global. If this constructor
    /// were to be called in multiple places at the code, there would be
    /// multiple `Timer` instances, all interfacing to the same global RTT
    /// hardware. The different instances could interfere, for example when
    /// setting alarms.
    ///
    /// Please make sure you only instantiate one timer per program, for that
    /// reason.
    pub unsafe fn new() -> Timer {
        // `Timer` has a private unit (`()`) field, to make it impossible to
        // create an instance, except by using this constructor.
        Timer(())
    }

    pub fn value(&self) -> u32 {
        // This way of reading the timer value may not be accurate.  According
        // to section 13.4 of the data sheet:
        // "As this value can be updated asynchronously from the Master Clock,
        //  it is advisable to read this register twice at the same value to
        // improve accuracy of the returned value."
        //
        // I'm not sure what that actually means. Can the value be updated in
        // the background, so that only some bits have changed? In that case
        // it might make some sense to read twice, to make sure the update has
        // finished.
        // I don't really buy that though. I'm guessing that writing the value
        // is atomic and I can't really read some in-between state. In that
        // case, reading twice doesn't make any sense and I don't really
        // understand what that comment from the data sheet means.
        unsafe {
            (*RTT).value.read()
        }
    }

    /// Sets the alarm with the given delay.
    ///
    /// The alarm interrupt is enabled in `Timer::new`. This means that the
    /// alarm will trigger an interrupt, if RTT interrupts are enabled in
    /// general.
    ///
    /// Please note that this method is not completely precise, as the timer
    /// resolution is 1024 Hz, not 1000 Hz. Please don't use it for serious
    /// timekeeping.
    pub fn set_alarm(&mut self, delay_ms: u32) {
        let alarm_ms = Wrapping(self.value()) + Wrapping(delay_ms);
        unsafe {
            (*RTT).alarm.write(alarm_ms.0)
        }
    }

    /// Sleep for the given number of milliseconds.
    ///
    /// This function configures the RTT and the NVIC as required, but doesn't
    /// currently reset the configuration. This doesn't matter in the context
    /// of the current program, but it might be nicer to reset everything to
    /// the previous value, if this were used in a larger program where other
    /// parts of the code might also sleep.
    pub fn sleep_ms(&self, milliseconds: u32, nvic: &mut Nvic) {
        let prescaler_value = 0x00000020; // millisecond resolution (roughly)
        let interrupt_mask  = 0x00010000; // enable alarm interrupt
        unsafe {
            (*RTT).mode.write(interrupt_mask | prescaler_value);
        }

        nvic.enable_rtt();

        // TODO: Since the timer resolution is 1024 Hz and not 1000 Hz, this
        //       function is not completely precise. Please don't use it for
        //       serious timekeeping.
        // TODO: This function doesn't really sleep. Rather, it waits busily,
        //       wasting a lot of resources.
        // TODO: The behavior of this function is wrong, if the addition wraps.
        //       Instead of sleeping, the function will return immediately.
        let sleep_until = Wrapping(self.value()) + Wrapping(milliseconds);
        while self.value() < sleep_until.0 {}
    }
}
