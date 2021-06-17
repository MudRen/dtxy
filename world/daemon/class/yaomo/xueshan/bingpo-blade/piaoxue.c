#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int i,num,skill;
  int cd = 10;
  int force_rate = 12;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչƮѩ��ʽ��\n");
        if(!wizardp(me) && me->query("family/family_name") != "��ѩɽ")
                return notify_fail(HIW"��Ʈѩ��ʽ��"+NOR"�Ǵ�ѩɽ����֮�ܣ�\n");
        if(!me->is_fighting(target))
                return notify_fail("��Ʈѩ��ʽ��ֻ����ս����ʹ�ã�\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("�������������\n");
        if ( me->query("piaoxue_known") < 2 ) //��ʱ��Ϊ2���׶� 2,3
           return notify_fail("��û��ѧ���Ŀھ�����ô�����򵽡�Ʈѩ��ʽ���İ��أ�\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("piaoxue_end") < cd )
          return notify_fail("��������Ϣ���ң��޷�ʹ�á�Ʈѩ��ʽ����\n");
        if(me->query_skill("blade", 1) < 200 || me->query_skill("bingpo-blade", 1) < 200)
                return notify_fail("��ĵ������𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("force", 1) < 200 || me->query_skill("ningxie-force", 1) < 200)
                return notify_fail("����ڹ����𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("spells", 1) < 200 || me->query_skill("dengxian-dafa", 1) < 200)
                return notify_fail("��ķ������𻹲�����ʹ����һ�л������ѣ�\n");
        if( me->query("lunhui_zhuanshi") > 4 )
                  force_rate = 8;
        else if( me->query("lunhui_zhuanshi") > 3 )
                  force_rate = 10;
        if( me->query("force_factor") / 3 > me->query_skill("force") / force_rate )
        	return notify_fail("�����̫���޷�ʹ������������ʽ��\n");
        weapon=me->query_temp("weapon");
        if( weapon->query("material") != "ice" )
        	return notify_fail("�������̫�أ��޷�ʹ���������ʽ��\n");
        
        me->set_temp("piaoxue_end",time());
   	enhance=me->query_skill("dengxian-dafa",1);
    	damage=me->query_skill("ningxie-force",1);
    		
  	message_vision(HIW"\n$N������"+weapon->name()+HIW"�������𣬿��к�Ȼ���������ѩ��\n"NOR,me,target);
  	message_vision(HIW"ѩ�����������$n�����ߣ�$N�����ȥ���Ρ�\n"NOR,me,target);
	message_vision(WHT"\n$n�޷��ҵ�$N����Ӱ���������˷��硣\n"NOR,me,target);  	
 	message_vision(HIC"\n$Nһ����Х�����ѩ֮��ʩչ���ˡ�"+BLINK+HIW"Ʈѩ��ʽ"+NOR+HIC"����\n"NOR,me,target);  	
    	
   	if( me->query("piaoxue_known") > 2 && target->query_temp("jldl"))
   	{
        	if( random(enhance) >  target->query_skill("wuxiangforce",1) )
                {
                	target->delete_temp("jldl");
                	target->set_temp("jldl_end", time() );
                	target->receive_wound("kee",damage,me);
 			message_vision(HIR"\n$n��Ҫ��$N֮��������ͻȻ���������ɽ裬�����пտյ������쳣���ܣ�\n"NOR,me,target);
 			COMBAT_D->report_status(target);
 		}
 		else
 		{
 			target->set_temp("jldl_temp",1);
 			target->delete_temp("jldl");
 			message_vision(HIR"\n$N��������������$n�Ľ���������������֮�أ�\n"NOR,me,target);
 		}
	}
	if(!target->is_busy()) target->start_busy(1);
	skill = damage + enhance + me->query_skill("bingpo-blade",1) + me->query_skill("blade", 1);
	num = skill/60;
	num = num/3;
	if( num > 9 ) num = 9;
	    
	target->add_temp("apply/dodge",-enhance/2);
	target->add_temp("apply/parry",-damage/2);
	me->add_temp("apply/attack",enhance/2);
	me->add_temp("apply/damage",damage/2);
	    
	for(i=1;i<=num;i++)
	{
		if( me->query("piaoxue_known") > 2 ) me->set_temp("piaoxue",i);
	   	COMBAT_D->do_attack(me, target,weapon);
	}
	if( target->query_temp("jldl_temp") )
	{
		target->set_temp("jldl",1);
	   	target->delete_temp("jldl_temp");
	}
	me->delete_temp("piaoxue");
	me->start_busy(2);
	me->add("force", -(100+num*30));
	target->add_temp("apply/dodge",enhance/2);
	target->add_temp("apply/parry",damage/2);
	me->add_temp("apply/attack",-enhance/2);
	me->add_temp("apply/damage",-damage/2);
	if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
	{ 
		str=me->name()+NOR+HIM"���ѩ֮��ʹ����"BLINK+HIW"Ʈѩ��ʽ"NOR+HIM"������˵"+target->name()+NOR+HIM"����ѩ��û����Ϣ������";
	    	message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
	return 1;
}
