#include <ansi.h>

inherit SSERVER;
//inherit F_CLEAN_UP;

int perform(object me, object target)
{
        object weapon;
	int i,j,k,damage;
	weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ����˭��\n");

        if(!me->is_fighting(target))
                return notify_fail("����û���ڴ�ܣ�\n");
	if(!wizardp(me) && me->query("family/family_name")!="���ƶ�")
           return notify_fail("�����ڡ�ֻ�л��ƶ����˲ſ����ã�\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("����ڹ�̫�\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

	if((int)me->query_skill("pingtian-dafa", 1) < 100)
        	return notify_fail("���ƽ��󷨵ȼ�����������ʹ����һ�У�\n");
	i=(int)me->query("combat_exp");
       	j=(int)target->query("combat_exp");
        k=(int)me->query_skill("spear");
        if(k<180)        
        	return notify_fail("���ǹ�����𻹲�����ʹ����һ�л������ѣ�\n");
        if( time()-(int)me->query_temp("buhui_end") < 4 )
                return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
        me->set_temp("buhui_end",time());
        me->delete("env/brief_message");
	target->delete("env/brief_message");
	message_vision(HIB"\n$Nһͦ����"+weapon->name()+NOR+HIB"ֱ��$n��\n"NOR,me,target);
	if (random(i)>j/2) 
	{
		damage=k+(int)me->query_str();
		target->receive_damage("kee",damage,me);
            	target->receive_wound("kee",damage/2,me);
	 	COMBAT_D->report_status(target);
	}
	else
	{
		message_vision(HIM"\n$Nһǹ�̿գ�����һ�⣬�Ի���$n��\n"NOR,me,target);
		if (random(i)> j/3 ) 
		{
	            	damage=k+random(k)+(int)me->query_str();
			target->receive_damage("kee",damage,me);
	            	target->receive_wound("kee",damage/2,me);
		 	COMBAT_D->report_status(target);
		}
		else
		{
		        message_vision(HIB"\n$Nһ���ֿգ����Բ����ţ�һͷײ��$n��\n"NOR,me,target);
			if (random(i)> j/4) 
			{
				damage=k*2+random(k)+(int)me->query_str();
				target->receive_damage("kee",damage,me);
		            	target->receive_wound("kee",damage/2,me);
			 	COMBAT_D->report_status(target);
			}
			else
			{
				message_vision(HIM"\n$N�ۼ�һͷײ�գ�����һ�������ħ�ķ���ȫ��֮��ײ��$n��\n"NOR,me,target);
				if (random(i)> j/5 ) 
				{
			     		damage=k*3+random(k)+(int)me->query_str();
					target->receive_damage("kee",damage,me);
			            	target->receive_wound("kee",damage/2,me);
				 	COMBAT_D->report_status(target);
				}
				else 
				{
			            	message_vision(HIW"\n$n������Ц��ֻ��ƥ��ֻ�����к��ã����ɱܿ���\n"NOR,me,target);
				}	
			}
		}
	}
	if (wizardp(me) && me->query("env/combat")=="verbose")
		tell_object(me, sprintf(HIC "damage: %d\n" NOR, damage));
	me->receive_damage("sen", 50);
        me->add("force", -100-damage/5);
	me->receive_damage("kee", 30); 
	
	me->start_busy(1+random(2));
        return 1;
}
