// shoupi.c

#include <armor.h>

inherit FINGER;

void create()
{
        set_name("ָ??", ({"finger"}));
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

