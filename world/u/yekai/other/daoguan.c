#include <armor.h>
#include <ansi.h>

inherit HEAD;

void create()
{
          set_name("红木道冠(人造人" + HIR"血祭"NOR + "过的)", ({ "bonnet", "hat" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "顶");
		set("long", "一顶硬红木的道冠。\n");
                set("material", "steel");
                set("value", 100);
                  set("armor_prop/armor", 100+random(20));
                  set("armor_prop/intelligence", 110+random(10));
                  set("armor_prop/personality", 100+random(20));
        }
        setup();
}

