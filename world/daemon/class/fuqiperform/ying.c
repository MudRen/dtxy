#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string msg;
        string *style_mix= ({
HIG "$N����һЦ������Ѹ�ٷ���һ�С�\n" NOR,
HIW "$N��Ȼ���֣�ʹ�÷��˴�Լ��Ʈ���ޱȡ�\n" NOR,
HIG "$N͵����������ػ���\n" NOR,
HIW "$N����˫�գ�������ɬ��\n" NOR,
HIG "$Nʹ�����һ�У����������ſ�����컡�\n" NOR,
});

	int extra_me, extra_you,i,gen;
	object you;
	
	if( !target ) target = offensive_target(me);
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("��������ӳ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(!me->query("married"))
          return notify_fail("����δ��飬ʹ������������ӳ�ݡ�\n");
        if(!objectp(you=present(me->query("couple/id"),environment(me))))
          return notify_fail("�����ż���ڴ˴���\n");
	if(me->is_busy()||you->is_busy())
	  return notify_fail("������æ���أ�\n");
	extra_me=(int)me->query_temp("apply/damage")+(int)me->query_str()*(int)me->query_str()/30;
	extra_you=(int)you->query_temp("apply/damage")+(int)you->query_str()*(int)you->query_str()/30;
        me->add_temp("apply/damage",(extra_you+extra_me)/2);
        you->add_temp("apply/damage",(extra_you+extra_me)/2);
        if(me->query("gender")=="����")gen=0;
        else gen=1;
        
        you->kill_ob(target);
        message_vision(HIC"$N������ʽ��Ȼ�ӽ����γ�һƬ���ֺ�ա�����̵صĹ⾰��\n"
                       +"$n��$NһЦ������Ծ��ս�š�"NOR,me,you);
	for(i=0;i<sizeof(style_mix);i++)
	if(i%2==gen){
	  message_vision(style_mix[i],me);
	  COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_REGULAR);
	}
	else{
	    message_vision(style_mix[i],you);
	    COMBAT_D->do_attack(you,target,you->query_temp("weapon"),TYPE_REGULAR);
	}

        me->add_temp("apply/damage",-(extra_you+extra_me)/2);
        you->add_temp("apply/damage",-(extra_you+extra_me)/2);
        message_vision(HIC"��һ·�书ʹ����$N��$n���ж��̺������޵��������⡣"NOR,me,you);
	me->start_busy(2);
	you->start_busy(2);
	return 1;
}

