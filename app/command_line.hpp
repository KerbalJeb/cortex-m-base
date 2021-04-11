#pragma once
#include "usb_serial.hpp"
#include <array>
#include <concepts>
#include <cstring>

namespace
{

struct command
{
  typedef void cmd_function ();
  cmd_function *execute;
  const char *cmd_name;
  const char *help_msg;
};

void
help ()
{
  usb_cout << "Help CMD Entered...";
}

std::array command_table = { command{ &help, "help", "" } };
}

class command_line
{
public:
  static void
  init ()
  {
    usb_serial::init ();
    (void)xTaskCreateStatic (&task, "cli", stack_size, nullptr, 1, stack,
                             &static_task);
  }

private:
  static constexpr std::size_t stack_size = configMINIMAL_STACK_SIZE;
  static inline StackType_t stack[stack_size]{};
  static inline StaticTask_t static_task{};

  [[noreturn]] static void
  task (void *params)
  {
    (void)params;
    char cmd_name[32];

    while (true)
      {
        usb_cout << cli::format::endl
                 << usb_shell.prompt << cli::format::flush;

        int status = usb_cin.get_line (' ', cmd_name, sizeof (cmd_name));
        if (status != 0)
          {
            /*todo add proper error handling*/
            continue;
          }
        if (cmd_name[0] == '\0')
          {
            /* Empty string */
            continue;
          }
        bool found_cmd = false;

        for (auto &cmd : command_table)
          {
            if (std::strcmp (cmd_name, cmd.cmd_name) == 0)
              {
                cmd.execute ();
                found_cmd = true;
                break;
              }
          }

        if (!found_cmd)
          {
            usb_cout << cmd_name << " not found";
          }
      }
  }
};
