//
// Created by Ben on 2021-03-27.
//

#include "usb_serial.hpp"

extern "C" void tud_cdc_rx_cb (uint8_t itf)
{
  (void)itf;
  usb_shell.receive();
  (void)tud_cdc_write_flush();
}

extern "C" void USB_IRQHandler ()
{
  tud_int_handler (0);
}

extern "C" void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts)
{
  (void) itf;
  (void) rts;

  // connected
  if ( dtr )
  {
    usb_shell.connected();
  }
}

[[noreturn]] void usb_serial::usb_device_task (void *pv)
{
  (void)pv;

  // This should be called after scheduler/kernel is started.
  // Otherwise it could cause kernel issue since USB IRQ handler does use RTOS queue API.
  (void)tusb_init ();

  // RTOS forever loop
  while (true)
  {
    // tinyusb device task
    tud_task ();
  }
}