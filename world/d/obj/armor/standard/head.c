// shoupi.c

#include <armor.h>

inherit HEAD;

void create()
{
        set_name("ͷ??", ({"head"}));
	set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "iron");
                set("unit", "??");
		set("armor_prop/armor", 1);
        }
        setup();
}

