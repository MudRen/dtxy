#include <ansi.h>
#include <weapon.h>

//inherit F_UNIQUE;
inherit STAFF;

void create()
{
	set_name( HIR "ʤ��Ů��" NOR, ({ "shengli nvshen", "staff" }) );
    set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell",1);
                set("no_drop", 1);
                set("no_get", 1);
				set("no_give", 1);
                set("no_put", 1);
		set("long", HIY "����ʤ��Ů�������ɵġ�\n" NOR);
		set("value", 1000);
		set("material", "brass");
		set("wield_msg", HIY "\n$N�ó�ʤ��Ů���������У�����ʥ�򶼴����˻ƽ�ʥ�µĹ�����.\n\n" NOR);
		set("unwield_msg", HIY "\n$N�������е�ʤ��Ů�񣬻ƽ�ʥ��Ҳ�漴ֹͣ�˹���.\n\n" NOR);
	}

    init_staff(200);
    set("special_effects", "��");  // emotion
	setup();
}
