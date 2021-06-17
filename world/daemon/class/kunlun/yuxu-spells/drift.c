// drift_sense.c

#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
	if( me->is_fighting() )
		return notify_fail("ս�����޷�ʹ�ý���ݵط���\n");
        if( me->query("mana") < 800 )
                return notify_fail("��ķ���������\n");
        if( me->query("sen") <= 500 )
                return notify_fail("��ľ���̫�\n");
        if( time()-(int)me->query_temp("xiao_end") < 30 )
          return notify_fail("�ݵؽ�ⷨ��������ʹ�ã�\n");
        if( me->query("faith")<100)
                return notify_fail("����������ɽ���鶴��������������ʹ�ý���ݵط���\n");
	if( me->is_ghost())
		return notify_fail("����޷�ʹ�ý���ݵط���\n"); 	
        if(me->query("family/family_name") != "����ɽ���鶴" )
                return notify_fail("����������Ե,���򲻵������ɷ��ľ���!!\n");
	if( target )
		return notify_fail("����ݵط�ֻ�ܶ��Լ�ʹ�ã�\n");
	write("��Ҫ�ƶ�����һ������ߣ�");
	input_to( (: call_other, __FILE__, "select_target", me :));
	return 1;
}

void select_target(object me, string name)
{
	object ob;

	if( !name || name=="" ) {
		write("��ֹʩ����\n");
		return;
	}

	ob = find_player(name);
	if( !ob || !me->visible(ob) || wizardp(ob) )
		ob = find_living(name);
	if( !ob || !me->visible(ob) || wizardp(ob) || !environment(ob)) {
		write("���޷����ܵ�����˵����� ....\n");
		write("��Ҫ�ƶ�����һ������ߣ�");
//		input_to( (: call_other, __FILE__, "select_target", me :));
		return;
	}
	if( me->is_fighting() ) {
		write("ս�����޷�ʹ�ý���ݵط���\n");
		return;
	} else if( me->query("mana") < 800 ) {
		write("��ķ���������\n");
		return;
	}

	me->add("mana", -75);
	me->receive_damage("sen", 30);
	
        message_vision( HIY "$N��ͷ��Ŀ����ʼʩչ����ݵ��� ....\n" NOR, me);
  	me->set_temp("xiao_end",time());
        if( random(ob->query("max_mana")) < (int)me->query("mana") / 5 ) {
		write("����ܵ��Է������������ǲ���ǿ�ҡ�\n");
		return;
	}
	if( random(me->query_skill("spells")) < (int)ob->query("mana") / 50 ) {
		write("����Ϊ����������ʧ���ˡ�\n");
		return;
	}
        if( random(50) > 
	(int)(me->query_skill("yuxu-spells",1))){
                write("����Ϊ����������ʧ���ˡ�\n");
                return;
        }
        message( "vision", HIY "\nһ��ҫ�۵Ĺ�â��Ȼ��ס" + me->name() 
                + "��һ�����������£���â����һ����ʧ����Ӱ���٣�\n\n", environment(me), ({ me }) );
	me->move(environment(ob));
        me->start_busy(5);
	message( "vision", HIY "\n�����ǰͻȻ����һ��ҫ�۵Ĺ�â����â�и��ֳ�һ����Ӱ��\n\n" NOR,
		environment(ob), ({ me }) );
}


