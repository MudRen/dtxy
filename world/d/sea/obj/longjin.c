// blade.c
#include <ansi.h>

#include <weapon.h>
inherit F_UNIQUE;

inherit WHIP;

void create()
{
        set_name(HIY"������"NOR, ({"ruan longjin", "longjin","whip"}));
        set_weight(10000);
        set("no_sell",1);
        if( clonep() )
                set_default_object(__FILE__);
        else {

set("long",HIC"һ����Լ�����ߵ�������ʵؼ�̣��������࣬�����Ƴɱ��ӵ���Ѳ��ϣ�\n"NOR);
                set("unit", "��");
	set("replace_file", "/d/obj/weapon/whip/pibian");
		set("wield_msg", HIC"ֻ��$N��������һ����ɫ����������죬����������\n"NOR);
		set("unwield_msg", "$N������$n�������䣮\n");
		set("weapon_prop/courage", 5);
        }
        init_whip(200);
        set("is_monitored",1);
        setup();
}
int query_autoload() { return 1; }


