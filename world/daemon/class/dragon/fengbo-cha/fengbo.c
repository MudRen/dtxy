//jiz.

#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	int mypot,tapot,time;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("���޾��粨��ֻ����ս���в���ʹ�á�\n");
        if(me->query("family/family_name")!="��������")
                return notify_fail("���������Ӳ����á��粨����\n");
	if( (int)me->query_skill("fengbo-cha", 1) < 50 ) 
		return notify_fail("�����Ϊ�������ʹ������һ�У�\n");
        if(me->is_busy())
                return notify_fail("��̫æ�ˣ�\n");;
	if( target->is_busy() )
		return notify_fail(target->name()+"�Ѿ���æ�ˣ���ʹ����Ư��Ҳ����ע�⵽��\n");
//        if(me->query_temp("dhwl")) 
//                return notify_fail("����������֮�У��Ļ���������޾��粨����\n");
	message_vision(HIC"$N��չ��������һ�棬��һ�棬�ó�������С�⻷��$n��ȥ��
�俴��������������ȴ�����ﲨ�����಻����ʵ�ǰ���ɱ����\n\n"NOR,me, target);

	//mypot=(int)me->query_skill("fork");
	//mypot=mypot*mypot*mypot/10 + random( (int)me->query("combat_exp"));
	mypot = (int)me->query("combat_exp");
	//tapot=(int)target->query_skill("parry");
	//tapot=tapot*tapot*tapot/10 + random( (int)target->query("combat_exp"));
	tapot=(int)target->query("combat_exp");

	time=(int)me->query_skill("fork")/50;
      	if ( time > 8 ) time = 8;
        if ( time < 4  ) time = 4;

        if ( random( mypot + tapot/4 ) > tapot/3 ) {
		message_vision(HIR"$N��Ȼ����⻷��ס����ʱĿ�ɿڴ�����֪���룡\n"NOR,target);
//                target->start_busy(1+random(time));
target->start_busy(time/2+random(time/4));
me->start_busy(1);
                
	}else {
	message_vision(HIR"����ȷ��$N���ƣ����䲻����$n�������˸����ֲ�����\n"NOR,target,
me);
me->start_busy(1+random(time/4));
	}

        /*if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
                me->kill_ob(target);
        }*/
	return 1;
}
