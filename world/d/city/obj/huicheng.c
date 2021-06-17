#include <skill.h>
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("�سǷ�", ({"huicheng seal", "seal", "fu"}));
	set_weight(100);
	if(clonep())
    		set_default_object(__FILE__);
  	else {

        set("long","һ�Ż����˷�����ҷ�ֽ�������и����ġ��سǡ��֡�\n");
        set("unit", "��");
       set("value", 3000);
	set("no_put",1);
	set("no_sell",1);
	set("no_give",1);

	}
	set("special_effects", "��(ji)���˷��������س�");  // emotion
	setup();
}

void init()
{
    add_action("do_ji","ji");

}

int do_ji(string arg)
{
	object seal=this_object();
	object me=this_player();
	object where=environment(me);


	if(!arg || (arg!="huicheng seal"
                        && arg!="seal"
                        && arg!="fu") )
		return notify_fail("��Ҫ��ʲô��\n");

	if(me->is_busy())
		return notify_fail("����æ���أ��޷����سǷ���\n");
	if( where->query("no_magic"))
		return notify_fail("���ﲻ�ܼ��سǷ���\n");

         if(me->query_temp("in_tiaozhan"))
                return notify_fail("�㻹����ս�У���ô���뿪�أ�\n");

	if( (int)me->query("mana") < 100 )
		return notify_fail("��ķ������ܿ��ƻسǷ���\n");
	if( (int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬���Ѽ�Ԧ�سǷ���\n");
        if(me->query_temp("in_tiaozhan"))
               return notify_fail("�㻹����ս�У���ô���뿪�أ�\n");

	message_vision(HIC"\n$N��һ�����ߡ�����һ�ӣ�������һ�ŻسǷ�������\n"NOR, me);
        message_vision(HIC"ֻ����ɳէ��$N����һ����,��Х��ȥ��\n"NOR, me);
       me->set("mana",0);
        me->start_busy(2+random(2));
        me->move("/d/city/kezhan");
        message("vision", HIC"һ���ɳ��ʯ����"+me->name()+"����ӰͻȻ����������ǰ��\n"NOR,
				  environment(me), me);
		tell_object(me, HIC"�������������ǻ����ˡ�\n"NOR);
	destruct(seal);
	return 1;

}
