// blade.c

#include <weapon.h>

inherit WHIP;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
        set_name("鞭", ({"whip"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一种灌注了神力的鞭，");
                set("unit", "条");
                set("value", 500);
        }
        init_whip(15);
        setup();
}

