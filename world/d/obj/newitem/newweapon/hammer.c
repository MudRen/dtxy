#include <weapon.h>

inherit HAMMER;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
        set_name("锤", ({ "hammer" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把沉重的锤子，打造的相当坚实，");
                set("value", 300);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，试了试重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(15);
        setup();
}

