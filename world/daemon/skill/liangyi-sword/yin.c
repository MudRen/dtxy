// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */

#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
	string msg;
	int extra, myexp, hisexp;
	object weapon;
	if( !target ) target = offensive_target(me);
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(me->query("family/family_name") != "����ɽ���Ƕ�" )
                return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á����־���?\n");
	if(target->is_busy())
		return notify_fail("�Է���æ���أ���\n");
	extra = me->query_skill("liangyi-sword",1) ;
	if ( extra < 120) return notify_fail("���[���ǽ���]���������죡\n");
        if((int)me->query("force") < 150 ) return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 150 ) return notify_fail("���޷����о�����\n");
               me->add("force", -100);
             me->receive_damage("sen", 100);
	weapon = target->query_temp("weapon");
	myexp = me->query_skill("sword");
	hisexp = target->query_skill("dodge",1)+target->query_skill("parry",1);
	extra = extra / 30;
	if( extra > 8 ) extra = 8;
	if(random(hisexp) < myexp && weapon)   
	{	
		message_vision(HIB "\n\n$Nʹ��һʽ���ǽ����еģ����־��ݣ�����"+(me->query_temp("weapon"))->name()+"��$n�ı���Խ��Խ����$nһ���ѳֲ�ס������"+ weapon->name()+  "���ֶ��ɣ�\n\n" NOR, me,target);
		target->start_busy(1+extra/4);
	     	weapon->unequip();
		if( weapon->unequip()) weapon->move(environment(target));
	}
	else
	{
		message_vision(HIB "\n\n$Nʹ��һʽ���ǽ����еģ����־��ݣ�����"+(me->query_temp("weapon"))->name()+  "��$nԽ��Խ�����Ƶ�$nһ����æ���ң�\n\n" NOR, me,target);
		if(random(hisexp) < myexp)
		{
			target->start_busy(1+extra/4+random(extra/2));
		}
		else 
		{
			message_vision(HIB "\n$n��Ϊ����վ�˸�����������У�\n" NOR, me, target);
		}
	}
	me->start_busy(1+random(2));
	me->improve_skill("liangyi-sword", 1, 1);
	return 1;
}
