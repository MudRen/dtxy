#include <weapon.h>

inherit RAKE;

void create()
{
        set_name("??????", ({ "dragon rake", "pa","rake" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "??");
                set("value", 5000);
                set("material", "iron");
                set("long", "һ?????????߳ݸְҡ?\n");
                set("wield_msg", "$N????һ??$n????ͷ?ϻ?????һȦ??\n");
        }
        init_rake(50);
        setup();
}

