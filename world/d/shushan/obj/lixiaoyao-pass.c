#include <armor.h>
#include <ansi.h> 
inherit HEAD;
inherit F_UNIQUE;
void create()
{
        set_name(BLU"����ͷ��"NOR, ({ "lixiaoyao xinwu","xinwu","lanbu toujin","toujin" }) );
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("long", "һ�����������Ƴɵ�˿��������������\n");
                set("value", 300);
                set("replace_file", "/d/obj/cloth/wulingjin");
				set("material", "cloth");
                set("armor_prop/armor", 100);
		set("armor_prop/personality", 1);
        }
        setup();
}

