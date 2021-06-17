// changjian.c 长剑

#include <weapon.h>
inherit SWORD;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
	set_name("剑", ({"sword" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是一柄灌注了神力的剑，只有高级剑客才能配带此剑，");
		set("value", 500);
		set("material", "steel");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
	}
	init_sword(25);
	setup();
}
