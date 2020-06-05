ENTRY(_start)

SECTIONS {
    . = 0x100000;
    
    _kern_s = .;
    
    .text  ALIGN(4096) :  {
        _kern_text_s = .;
        *(.text)
        _kern_text_e = .;
        
    }
    
    .rodata ALIGN(4096) : {
        _kern_rodata_s = .;
        *(.rodata)
        _kern_rodata_e = .;
    }
    
    .data  ALIGN(4096):  {
        _kern_data_s = .;
        *(.data)
        _kern_data_e = .;
    }
    
    .bss ALIGN(4096) :  {
        _kern_bss_s = .;
        *(.bss)
        _kern_bss_e = .;
    }
    
    .stack ALIGN(4096) (NOLOAD) :  {
        _kern_stack_s = .;
        *(.stack)
        _kern_stack_e = .;
    }
    
    _kern_e = .;
}
