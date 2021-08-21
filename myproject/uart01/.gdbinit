target remote localhost:4441

define ram
monitor reset
monitor soft_reset_halt
load $arg0
monitor reg pc 0x10000000
monitor resume
end
