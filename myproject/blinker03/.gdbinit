target remote localhost:4441

define ram
monitor reset
monitor soft_reset_halt
load main.axf
monitor reg pc 0x100000f1
monitor resume
end
