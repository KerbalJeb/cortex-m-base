//
// Created by Ben on 2021-03-27.
//

#pragma once

#include "tusb.h"
#include "shell.hpp"
#include "stm32f0xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "volatile_op.hpp"


class usb_serial
{
 public:
  static void puts (const char *s)
  {
    (void)tud_cdc_write_str (s);
  }

  static void putc (const char c)
  {
    (void)tud_cdc_write_char (c);
  }

  static void flush ()
  {
    (void)tud_cdc_write_flush ();
  }

  static int getc ()
  {
    return tud_cdc_read_char ();
  }

  static void init ()
  {
    (void)xTaskCreateStatic (&usb_device_task, "usb", usb_task_stack_size, nullptr,
                             configMAX_PRIORITIES - 1, usb_task_stack, &usb_task);
  }

  static int peek (int idx)
  {
    uint8_t value;
    if (tud_cdc_peek (idx, &value))
    {
      return value;
    }
    return -1;
  }
 private:
  static constexpr std::size_t usb_task_stack_size = 90;
  static inline StackType_t    usb_task_stack[usb_task_stack_size];
  static inline StaticTask_t   usb_task;
  [[noreturn]] static void usb_device_task (void *pv);
};

inline cli::shell<usb_serial, blocking_ring_buffer<char, 32>> usb_shell{"$ ", "Example USB CLI Interface"};
inline auto& usb_cout = usb_shell.cout;
inline auto& usb_cin = usb_shell.cin;