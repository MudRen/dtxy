#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
	object weapon;
	int damage;
      	string msg,str; 
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С���ѩ��������\n");
    	if(!wizardp(me)&&(string)me->query("family/family_name") != "��ѩɽ" )
   		return notify_fail("��ı��Ǻ����Ǵ�����͵ѧ���ģ�\n");
        if(!me->is_fighting())
                return notify_fail("����ѩ������ֻ����ս����ʹ�ã�\n");
        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");
        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("bingpo-blade", 1) < 100)
                return notify_fail("��ı��Ǻ������𻹲�����ʹ����һ�л������ѣ�\n");
        if(time() - me->query_temp("xs_pfm_busy") < 4) return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");
        me->add("force", -200);
        damage = 10 + me->query_skill("blade", 1)/2 + random(me->query_skill("bingpo-blade", 1)/2);
       	//target->add_temp("apply/dodge",-damage);
        //target->add_temp("apply/parry",-damage);
        if(!target->is_busy()) target->start_busy(1);
	message_vision(HIW"\n$N������������һת�����ܶ�ʱ�������ߣ������к�������$nֻ�������ǵĵֿ���\n"NOR,me,target);
 	message_vision(HIW"$Nһ����Ц����ѩ��֮�С�$n�󼱣�������Ѱ����Ȼ����һ�������ŵ����Ϯ����������\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        //target->add_temp("apply/dodge",damage);
        //target->add_temp("apply/parry",damage);
 	//if(random(me->query("combat_exp"))>random(target->query("combat_exp"))/5)
 	//{
		message_vision(HIY"\n����,һֻ��ɫ������ԶԶ������$N��$n�������ˣ�\n"NOR,me,target);
		message_vision(HIY"\nͻȻ�������ó��һ��,��ʱ��������\n"NOR,me,target);
		if(random(me->query("force_factor"))>target->query("force_factor")/5)
		{
 			message_vision(HIR"\n$N��������ʧ,��æ����һ�У�\n"NOR,me,target);
 			target->receive_damage("kee",damage*2); 
 			target->receive_damage("sen",damage*2); 
 			message_vision(HIR"\n����������ʯ�������,��$n�ҵñ������ˣ�\n"NOR,me,target);
 			target->receive_wound("kee",damage);
 			target->receive_wound("sen",damage);
 			COMBAT_D->report_status(target);
		}  
 		else if(random(me->query("force_factor"))>target->query("force_factor")/4)
		{
			message_vision(HIR"\n����������ʯ�������,��$n�ҵñ������ˣ�\n"NOR,me,target);
			target->receive_wound("kee",damage);
			COMBAT_D->report_status(target);
		}
		else  
		{
			message_vision(HIR"\n����������ʯ�������,��$N��$n�ҵñ������ˣ�\n"NOR,me,target); 
			target->receive_wound("kee",damage);
			target->receive_wound("sen",damage);
			COMBAT_D->report_status(target);
			me->receive_wound("kee",damage/10);
			COMBAT_D->report_status(me);
		}        
	//}
 	//me->receive_damage("sen", 100);
 	//me->add("force", -300);
    	if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
	{
		str=target->name()+HIM"��"+me->name()+"��ѩɽ�ش�"NOR+HIW"����ѩ������"+HIM"ɱ���ˣ���˵"+target->name()+"��ʬ�屻��ӡ��һ���޴��"NOR+HIW"����"+HIM"���棡";
		message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
 	}
 	if( me->query("lunhui_zhuanshi") )
 		me->start_busy(1);
 	else
        	me->start_busy(2);
      	me->set_temp("xs_pfm_busy", time());
        //call_out("remove_effect",2+random(2),me);
        return 1;
}

void remove_effect(object me) 
{
  	if (!me) return;
  	me->delete_temp("xs_pfm_busy");
}
