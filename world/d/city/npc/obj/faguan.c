#include <armor.h>

inherit HEAD;

void create()
{
        set_name("ħ�þ���", ({ "mohuan jinglun", "jinglun", "hat" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ���ں����ķ���,��˵����������ֵ�ħ����\n");
                set("material", "steel");
                set("value", 1000);
		set("no_sell", 1);
               set("no_give", 1);
               set("no_put", 1);
               set("no_drop", 1);
               set("no_get", 1);
                set("armor_prop/armor", 3);
                set("armor_prop/intelligence", 10);
		set("armor_prop/personality", 1);
        }
        setup();
}

