/*	
	���ģ���ɽ����7�������������7������
	
	������ū��
	�����佭��
	����������
	�ӽ�������
	�ؽ�����˼
	�⽣һ��÷
	����̤ɯ��
	
	�����������
��������������������죬�����У���
��������	�趯��֦��������磬�������졣
����������ϸ��ƽɳ����С���磡��
��������	ǣ��������������������
��������������Ļ��ƾ���˼�����
	����������羲ֹ��������ΪһĻ���磬ȴ�ֱ仯���
����������ĺ�����̻��--��
��������	���绯Ϊ˿˿�����ɢ��ɢ����ۡ�
���������������У���
		������������һʽ�Ѿۼ���һ�����Ϣ�籬�Ѱ�ը����
	
*/
#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int i;
  int cd = 10;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�����ġ���\n");
        if(!wizardp(me) && me->query("family/family_name") != "��ɽ��")
                return notify_fail(HIC"�����ġ�"+NOR"����ɽ����֮�ܣ�\n");
        if(!me->is_fighting(target))
                return notify_fail("�����ġ�ֻ����ս����ʹ�ã�\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("�������������\n");
        if ( !me->query("sword_known") ) //��ʱ��Ϊ2���׶� 1,2
           return notify_fail("��û�пھ����޷����򵽡����ġ��İ��أ�\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("sword_end") < cd )
          return notify_fail("��������Ϣ���ң��޷�ʹ�á����ġ���\n");
        if(me->query_skill("sword", 1) < 200 || me->query_skill("yujianshu", 1) < 200)
                return notify_fail("��Ľ������𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("force", 1) < 200 || me->query_skill("zixia-shengong", 1) < 200)
                return notify_fail("����ڹ����𻹲�����ʹ����һ�л������ѣ�\n");

    	weapon=me->query_temp("weapon");
    	enhance=me->query_skill("zixia-shengong",1);
	damage=me->query_skill("yujianshu",1);
	i = me->query("sword_known");
	damage = damage + damage/(10-i);
	//if( i > 3 )
  //  	{
	    	target->start_busy(1);
	//}
	i = 1 + random(i);
  
	message_vision(HIC"\n$N����$n�Ĺ���������˫��ĬĬ���"+weapon->name()+HIC"�е��鶯֮����\n"NOR,me,target);
	message_vision(HIC"\n$N��������˫�ۣ�����͸©���ľ��⣬����$n�޷����ӡ�\n"NOR,me,target);
	me->set_temp("sword_type", i);
	switch(i)
	{
		case 1:
     		{	
     			str=me->name()+"ʹ����ɽ������ѧ��"HIY"����"HIM"��"HIC"��ū��"HIM"����"+target->name()+NOR+HIM"������֮�������˻�Ȫ��";
			message_vision(HIC"\n$N����ոսӴ�"+HIY"��"+HIC"ʱ���˷�����顣\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"Ӧ�����Ŀ���⣬ֱָ$n��\n"NOR,me,target);
     			break;
     		}
     		case 2:
     		{	
     			str=me->name()+"ʹ����ɽ������ѧ��"HIY"����"HIM"��"HIG"�佭��"HIM"����"+target->name()+NOR+HIM"������֮�������˻�Ȫ��";
			message_vision(HIC"\n$N����ոտ�ʼ��"+HIY"��"+HIC"ʱ����ϲ��\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"Ӧ�������Ĳ�����\n"NOR,me,target);
     			break;
     		}
     		case 3:
     		{	
     			str=me->name()+"ʹ����ɽ������ѧ��"HIY"����"HIM"��"HIC"������"HIM"����"+target->name()+NOR+HIM"������֮�������˻�Ȫ��";
			message_vision(HIC"\n$N�����һ�θ�"+HIY"��"+HIC"����ʱ�ĳ��졣\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"Ӧ�������𶯡�\n"NOR,me,target);
     			break;
     		}
     		case 4:
     		{	
     			str=me->name()+"ʹ����ɽ������ѧ��"HIY"����"HIM"��"HIR"������"HIM"����"+target->name()+NOR+HIM"���ӽ�֮�������˻�Ȫ��";
			message_vision(HIC"\n$N���·����ƽ����"+HIY"��"+HIC"����ʱ������������\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"Ӧ���������罣â��\n"NOR,me,target);
     			break;
     		}
     		case 5:
     		{	
     			str=me->name()+"ʹ����ɽ������ѧ��"HIY"����"HIM"��"HIM"����˼"HIM"����"+target->name()+NOR+HIM"���ؽ�֮�������˻�Ȫ��";
			message_vision(HIC"\n$N����ͻ�֣���"+HIY"��"+HIC"����������֮�С�\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"Ӧ����ʧ������$Nȴɢ���������Ľ�����\n"NOR,me,target);
     			break;
     		}
     		case 6:
     		{	
     			str=me->name()+"ʹ����ɽ������ѧ��"HIY"����"HIM"��"HIW"һ��÷"HIM"����"+target->name()+NOR+HIM"���⽣֮�������˻�Ȫ��";
			message_vision(HIC"\n$N����ͻ�֣����⻯"+HIY"��"+HIC"��\n"NOR,me,target);
			message_vision(HIC"\n$NͻȻʧȥ��Ӱ��$n���ܸо����ޱ��޼ʵĽ�����\n"NOR,me,target);
     			break;
     		}
     		case 7:
     		{	
     			str=me->name()+"ʹ����ɽ������ѧ��"HIY"����"HIM"��"HIC"̤ɯ��"HIM"����"+target->name()+NOR+HIM"������֮�������˻�Ȫ��";
			message_vision(HIC"\n$N��"+HIY"����"+HIC"������ͨ������������\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"Ӧ�����ַɳ���\n"NOR,me,target);
     			break;
     		}
     		case 8:
     		{
     			str=me->name()+"ʹ����ɽ������ѧ��"+NOR+HIY"����"HIM"��"BLINK+HIR"�����"NOR+HIM"����"+target->name()+NOR+HIM"�������Ľ��������˻�Ȫ��";
			message_vision(HIC"\n"+weapon->name()+HIC"��������֮��������һʱ֮����˹�����\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"�����ѱ�����������㲨����������$n����Χס��\n"NOR,me,target);
     			break;
     		}
	}
	target->add_temp("apply/dodge",-enhance/2);
        target->add_temp("apply/parry",-damage/2);
        me->add_temp("apply/attack",enhance/2);
    	me->add_temp("apply/damage",damage/2);
    	me->set_temp("pfm_xjh", 0);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("pfm_xjh", 1);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("pfm_xjh", 2);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("pfm_xjh", 3);
    	COMBAT_D->do_attack(me, target, weapon);
	me->set_temp("pfm_xjh", 4);
    	COMBAT_D->do_attack(me, target, weapon);
    	
    	if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
      	{ 
        	message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
       	}
       	me->delete_temp("sword_type");
	me->delete_temp("pfm_xjh");
    	me->add("force", -300);
	me->start_busy(2);
	target->add_temp("apply/dodge",enhance/2);
        target->add_temp("apply/parry",damage/2);
        me->add_temp("apply/attack",-enhance/2);
    	me->add_temp("apply/damage",-damage/2);
    	me->set_temp("sword_end",time());	
    	
  return 1;
}
