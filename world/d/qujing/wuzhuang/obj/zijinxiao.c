//zijinxiao.c by yushu 2000.11
#include <weapon.h>
inherit F_UNIQUE;
inherit SWORD;
void create()
{
        set_name("�Ͻ���", ({"zijin xiao", "xiao"}));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
              set("unit", "��");
              set("long", "�����ӵ��Ͻ����˵�����Ϻ����������һ���������ġ�\n");
		set("no_sell", 1);
		set("no_put", 1);
              set("value", 30000);
		set("replace_file", "/d/obj/weapon/sword/yudi");
              set("material", "crimsonsteel");
              set("wield_msg", "$N�����Ͻ������������Ϊ����������Ϻ������ˡ�\n");
              set("unwield_msg", "$N����ή�ң��޾���ɵĽ��Ͻ��������䡣\n");
        set("weapon_prop/strength", 2);
	set("music/type", "xiao");

        }
        init_sword(75);
        set("is_monitored",1);
        setup();
}

