//Cracked by Roath
// pozhan.c 		�����ٳ�

#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	string msg;
	int delay, myblade;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("����ս���У�¶ʲô������\n");
	if(me->query("family/family_name")!="�ݿ�ɽ�޵׶�")
 return notify_fail("��������ֻ���޵׶����˲ſ����ã�\n");
	if( me->query("force") < 100 )
		return notify_fail("���������̣����Գ��С�\n");
	myblade=(int)me->query_skill("kugu-blade",1);
	if(myblade>160) myblade=160; // mon 12/7/98
	if(myblade<80) 
		return notify_fail("�����Ϊ�����¶��������̫Σ���ˡ�\n");

	delay = myblade/20;
	delay = delay/2 + random(delay/4);
	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
	me->add("force", -100);
	msg = CYN "$N����ʽͻȻһ�䣬���ȫ���·����������������ٳ���\n";
	//change totoal random to half random half ur own value to make the sucessrate more stable
        //if( ((random(me->query("combat_exp"))*3/4 + (me->query("combat_exp")/4) > (int)target->query("combat_exp")*3/8 ))) {
        if( random(me->query("combat_exp")) > target->query("combat_exp")/4 ) {
		msg += "$n�빥��ȴ��֪���ĸ��������棬�ĸ��Ǽ١�\n";
		msg += "���$p��$P���˸����ֲ�����\n" NOR;
		target->start_busy(delay);
		me->start_busy(random(2));
	} else {
		msg += "����$p������$P����ͼ����û���ϵ���\n" NOR;
                  me->start_busy(1);
	}
	message_vision(msg, me, target);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
                me->kill_ob(target);
        }

	return 1;
}
