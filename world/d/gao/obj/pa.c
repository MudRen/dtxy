// rake.c

#include <weapon.h>
#include <skill.h>
#include <ansi.h>

inherit ITEM;
inherit F_UNIQUE;
//inherit RAKE;

void create()
{
  set_name("С����", ({ "ding pa", "pa","rake" }) );
  set_weight(9000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("value", 100);
    set("no_drop",1);
    set("no_give",1);
    set("no_get",1);
    set("no_put",1);
    set("no_sell",1);
    set("time", 3);
    set("material", "iron");
    set("long", "һ�����Ӳӵ�С���ң���˵�ܴ���С��\n");
    set("wield_msg", "$N����һ��$n������������,���ҹ�Ȼ���ʮ�ֳ��֡�\n");
  }
  set("special_effects", "���Լ�(ji)");  // emotion
  setup();
}

void init()
{
  check_owner();
}

int ji_ob(object victim)
{
        object seal=this_object();
        object me=this_player();
        object where=environment(me);
	object zhu;

        if(me->is_busy())
                return notify_fail("����æ���أ��޷�����С���ҡ�\n");
        if( !victim)
                return notify_fail("��������˲������\n");
        if( where->query("no_magic"))
                return notify_fail("���ﲻ�ܼ�С���ҡ�\n");
        if( !me->is_fighting())
                return notify_fail("ֻ��ս���в��ܼ�С���ҡ�\n");
        if( (int)me->query("mana") < 1000 )
                return notify_fail("��ķ������ܿ���С���ҡ�\n");
        if( (int)me->query("sen") < 200 )
                return notify_fail("��ľ����㣬���Ѽ�ԦС���ҡ�\n");


        message_vision(HIC"\n$N��һ�����㡱����һ�ӣ�������$n������\n"NOR, me, seal);
message_vision(HIC"$n��������һ�·ɵ���գ�ֻ�����һ���������ȵ��䵽��$N���С�\n"NOR,me,seal);

	seteuid(getuid());
        zhu = new("/d/gao/npc/bajie");
        zhu->move(environment(me));
        zhu->invocation(me);
	zhu->set_temp("invoker",me);
        me->add("mana",-100);
	me->receive_damage("sen", 100);

        me->start_busy(3+random(3));

	add("time", -1);

	if( (int)seal->query("time") < 1) {
        destruct(seal);
	}
        return 1;
}

int ji (string target)
{
  object seal = this_object ();
  object me = this_player();
  string name=seal->query("name");
  object victim;

  if (!target)
    return notify_fail("�����˭��"+name+"��\n");

  victim=present(target,environment(me));
  return seal->ji_ob(victim);
}