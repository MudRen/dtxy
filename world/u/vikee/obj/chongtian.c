#include <ansi.h>
#include <weapon.h>

inherit F_UNIQUE;

inherit SWORD;

void create()
{
        set_name(HIM "����һ��" NOR, ({"chongtian sword", "sword"}));
        set_weight(14000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ����ɫ�Ľ��������ͼ��������Ѷ���\n");
		set("no_sell", 1);
		set("no_drop", 1);
		set("no_put", 1);
                set("value", 30000);
		set("replace_file", "/d/obj/weapon/sword/qingfeng");
                set("material", "crimsonsteel");
                set("wield_msg", "$N��üһ����$n���ȵ��������У�\n");
                set("unwield_msg", "$N�����У���$n�����������䣮\n");
        set("weapon_prop/int", 2);

        }
        init_sword(750);
        set("is_monitored",1);
        setup();
}

