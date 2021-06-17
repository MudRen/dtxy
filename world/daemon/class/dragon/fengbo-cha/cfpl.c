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
                return notify_fail("��Ҫ��˭ʩչ���˷����ˡ���\n");
        if(!wizardp(me) && me->query("family/family_name") != "��������")
                return notify_fail(HIC"���˷����ˡ�"+NOR"����������֮�ܣ�\n");
        if(!me->is_fighting(target))
                return notify_fail("���˷����ˡ�ֻ����ս����ʹ�ã�\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("�������������\n");
        if ( !me->query("cfpl_known") ) //��ʱ��Ϊ2���׶� 1,2
           return notify_fail("��û�пھ����޷����򵽡��˷����ˡ��İ��أ�\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
	
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("cfpl_end") < cd )
          return notify_fail("��������Ϣ���ң��޷�ʹ�á��˷����ˡ���\n");
        if(me->query_skill("fork", 1) < 200 || me->query_skill("fengbo-cha", 1) < 200)
                return notify_fail("��Ĳ淨���𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("hammer", 1) < 200 || me->query_skill("huntian-hammer", 1) < 200)
                return notify_fail("��Ĵ������𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("dragonfight", 1) < 200)
                return notify_fail("����Ʒ����𻹲�����ʹ����һ�л������ѣ�\n");
        if (me->query_skill_mapped("unarmed")!="dragonfight")
                return notify_fail("���˷����ˡ�����������β�������ʹ�á�\n");
        if (me->query_skill_mapped("hammer")!="huntian-hammer")
                return notify_fail("���˷����ˡ�������ϻ��촸������ʹ�á�\n");

    	weapon=me->query_temp("weapon");
    	message_vision(HIC"\n$N����̺���ͨ������"+weapon->name()+HIC"�����ػ�����������"+weapon->name()+HIC"�������κ��ˡ�\n"NOR,me,target);
    	message_vision(HIC"\n$N�����߳����˷����˻���ʱ��ȫ����������"+weapon->name()+HIC"��ɽ���������$n��\n"NOR,me,target);

	if( !target->is_busy() )
		target->start_busy(1);
	
	enhance=me->query_skill("dragonforce",1);
    	damage=me->query_skill("seashentong",1);
	target->add_temp("apply/dodge",-enhance/2);
        target->add_temp("apply/parry",-damage/2);
        me->add_temp("apply/attack",enhance/2);
    	me->add_temp("apply/damage",damage/2);
    	me->set_temp("HTH_perform", 1);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 2);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 3);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 4);
    	COMBAT_D->do_attack(me, target, weapon);
	
	message_vision(HIC"\n$n�����α�$N�����������˽�����û��\n"NOR,me,target);
    	if( me->query("cfpl_known") > 1 )
	{
		//�˷����˵ڶ��Σ�ֱ���Ʒ��ò׺�
		  me->add("force", -300);
		  message_vision(HIC"\n$N�����߳���ֱ���Ʒ��ò׺���\n"NOR,me,target);
		  message_vision(HIC"\n$nֻ��ǧ��ɾ��˷ֺ���ɢ��������˷����ҵ�ײ���Լ�����Ĥ��Ȼ���죬�·��Ҫը�ѡ�\n"NOR,me,target);
		  message_vision(HIC"\n$n��æ�����ֿ����ǿ�ã��ʹ֮���ʱ�����滺��\n"NOR,me,target);
		  message_vision(HIC"\n��$n����Խʢ����Խ�Ǿ�������������˱�����ӿ��ײ�����Լ���������������ȥ�������·�Ҫ��λһ�㡣\n"NOR,me,target);            
		  message_vision(HIC"\n$N�������˸�������߳����ȥ������"+weapon->name()+HIC"����һ���������$n��\n"NOR,me,target);
		  me->set_temp("HTH_perform", 5);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("HTH_perform", 6);
    	COMBAT_D->do_attack(me, target, weapon);
    	seteuid(getuid());
	    me->set("actions", (: call_other, SKILL_D("dragonfight"), "query_action" :) );
    	weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    	weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    	weapon->set("use_apply_skill",1);
    	weapon->set("apply/skill_type","unarmed");
    	message_vision(HIC"\n$N���ַ���һ�죬"+weapon->name()+HIC"����һ������ֱ�ɾ��졣\n"NOR,me,target);
    	message_vision(HIB"\n������$N����ǰ�ˡ�\n"NOR, me,target);    
    	COMBAT_D->do_attack(me, target,weapon);
    	message_vision(HIC"\n$N����һ���������߸�Ծ�𣬰���н�"+weapon->name()+HIC"���������С�\n"NOR,me,target);
    	message_vision(HIY"\n$N����ͻȻ��ת���£�����������׹�������ף�����"+weapon->name()+HIY"ֱ��$n��\n"NOR,me,target);
    	seteuid(getuid());
    	me->set("actions", (: call_other, SKILL_D("huntian-hammer"), "query_action" :) );
    	weapon->set("use_apply_skill",1);
    	weapon->set("apply/skill_type","hammer");
    	COMBAT_D->do_attack(me, target,weapon);
    	weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    	weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    	me->reset_action();
    	if ( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
      	{ 
      		str=me->name()+"ʹ��������ѧ"+NOR+HIC"���˷����ˡ�"+NOR+HIM"�Ծ�����£���"+target->name()+NOR+HIM"����������";
        	message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
       	}
	}
			me->delete_temp("HTH_perform");
    	me->add("force", -300);
	me->start_busy(2);
	target->add_temp("apply/dodge",enhance/2);
        target->add_temp("apply/parry",damage/2);
        me->add_temp("apply/attack",-enhance/2);
    	me->add_temp("apply/damage",-damage/2);
    	me->set_temp("cfpl_end",time());	
    	
  return 1;
}
