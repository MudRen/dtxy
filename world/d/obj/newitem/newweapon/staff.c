// hammer.c
#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit STAFF;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
        set_name("杖", ({"staff"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把灌注了魔力的杖，上面几个铁环叮当作响，");
                set("value", 500);
                set("material", "iron");
                set("wield_msg","$N拿出一把$n，握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_staff(25);
        setup();
}

