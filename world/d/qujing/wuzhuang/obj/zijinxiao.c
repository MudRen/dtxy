//zijinxiao.c by yushu 2000.11
#include <weapon.h>
inherit F_UNIQUE;
inherit SWORD;
void create()
{
        set_name("紫金箫", ({"zijin xiao", "xiao"}));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
              set("unit", "把");
              set("long", "韩湘子的紫金箫，听说是用南海紫竹林里的一株神竹做的。\n");
		set("no_sell", 1);
		set("no_put", 1);
              set("value", 30000);
		set("replace_file", "/d/obj/weapon/sword/yudi");
              set("material", "crimsonsteel");
              set("wield_msg", "$N拿起紫金箫，不禁想起了为这箫而被困南海的丽人。\n");
              set("unwield_msg", "$N神情萎靡，无精打采的将紫金箫插回腰间。\n");
        set("weapon_prop/strength", 2);
	set("music/type", "xiao");

        }
        init_sword(75);
        set("is_monitored",1);
        setup();
}

