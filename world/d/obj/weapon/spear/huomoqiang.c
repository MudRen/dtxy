// huomoqiang.c

#include <weapon.h>
#include <ansi.h>

inherit SPEAR;

void create()
{
        set_name(HIR "��ħǹ" NOR, ({ "huomoqiang", "spear" })
);
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��" HIR "��ħǹ" NOR "�����ǻ�ħ��������\n");
                set("value", 10000);
                set("material", "blacksteel");
                set("wield_msg","$N����ħǹ�������У���Χ���˶پ��������һ�֮�����\n");
		set("weapon_prop/courage", 8);
        }
        init_spear(150);
        setup();
}

