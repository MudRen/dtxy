// tongxin.c ����ͬо
// ����ϼ����ϼͬΪ��о����
// daemon/skill/chixin-jian/
// by kryos,  huarong edit / 2003-03-06
 
#include <ansi.h>
 
inherit SSERVER;

int perform(object me)
{
        string msg,str; 
        object weapon, target;
        object ob;
        int skill, skill2,extra,damage;
	int cd = 7;
        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qingxia-jian",1);
        skill2 = me->query_skill("yinsuo-jinling",1);
	//if(!wizardp(me))
        //	return notify_fail("��ʦ���ڲ���"+HIW+"������ͬо��"+NOR+"������\n");
        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("��������ʹ����ô��ʹ������ͬо����\n");

        if(me->query("family/family_name")!="��˿��")
                return notify_fail("���˽���ϼ����ϼ����֮��,������д���ᣡ\n");
                
        if( !me->is_fighting(target)|| !living(me) )
                return notify_fail("������ͬо��ֻ����ս����ʹ�á�\n");

//        if( me->query_temp("BAIFA_perform") ) 
//                return notify_fail("ʹ����������ʱ���ܷ������á�\n");

        if( (int)me->query("force") < 1000 )
                return notify_fail("�����ڵ��������㣡\n");
        
        if( (int)me->query("max_force") < 1500 )
                return notify_fail("�����ڵ��ڹ�̫�\n");
	if( me->query("lunhui_zhuanshi") > 3 )
		cd = 5;
	else if( me->query("lunhui_zhuanshi") )
		cd = 6;
        if( time()-(int)me->query_temp("xin_end") < cd )
                return notify_fail("�����ö�Ͳ����ˣ�\n");

        if( skill < 150)
                return notify_fail("������ϼ���ӵ��书��û�����ã���ôʹ�á�����ͬо��! \n");

        if( skill2 < 150)
                return notify_fail("������ϼ���ӵ��书��û�����ã���ôʹ�á�����ͬо��! \n");

        if( me->query_skill_mapped("sword") != "qingxia-jian") 
                return notify_fail("�������ϼ���ӵ���ϼ���������ʹ�á�����ͬо����\n");
                
        if( me->query_skill_mapped("whip") != "yinsuo-jinling") 
                return notify_fail("�������ϼ���ӵ��������壬���ʹ�á�����ͬо����\n");
        extra = skill + skill2;
        target->add_temp("apply/dodge",-extra/5);
        target->add_temp("apply/parry",-extra/5);
        me->add_temp("apply/attack",extra/5);
    	me->add_temp("apply/damage",extra/5);
        me->receive_damage("sen", 100);       
        message_vision(HIC"\n$N"+HIC+"ĬĬ������ϼ����ϼ����żȻ����ľ��ģ�$n"+HIC+"��$N"+HIC+"������࣬Խ��Խ�ǳ�Ͱ�����ȫ����������ʥ��Ĺ�ԡ�\n\n"NOR+
               WHT"$n"+WHT+"ֻ�����ܾ��������峪����Լ�����ʧȥ��$N"+WHT+"�����Ρ�\n "NOR, me,target);
       	message_vision(HIY"\n$N"+HIY+"�����⶯������һ������$n\n"NOR, me,target);
       	damage = COMBAT_D->do_attack(me, target, weapon);
	if (damage > 0)
        {
                message_vision(HIC"\n$n"+HIC+"����$N"+HIC+"�����ν����仯,����Ŀϸ��,��ǰ������һյ��ƣ�$N"+HIC+"ƮȻ���ڵ�յ֮�ϣ������裡\n"NOR,me,target);
                message_vision(HIY"\n$N"+HIY+"�����Ķ�������һ������$n\n"NOR, me,target);
                        damage = COMBAT_D->do_attack(me, target, weapon);
               	if (damage > 0 && skill > 199)
               	{
                       	message_vision(HIC"\n$n"+HIC+"ֻ��$N"+HIC+"�Ľ���Ʈ������,ȴ�Ǿ����쳣,������ۿ���$N"+HIC+"ȴ�Ѳ�������յ֮��һ��ɫ��������ȼ��\n"NOR,me,target);
                        message_vision(HIY"\n$N"+HIY+"�����������һ������$n\n"NOR, me,target);
                        damage = COMBAT_D->do_attack(me, target, weapon);
                        if (damage > 0 && skill > 249)
                        {
                               	message_vision(HIC"\n$n"+HIC+"���ӵ�յ,�߾�����Ѱ��$N"+HIC+"�����Σ�ȴ���ֵ�յ֮����ȼ��һ��ɫ���磡\n"NOR,me,target);  
                                message_vision(HIY"\n$N"+HIY+"�������������һ������$n\n"NOR, me,target);
                                damage = COMBAT_D->do_attack(me, target, weapon);
                                if (damage > 0 && skill > 299)
                                {
                                        message_vision(HIC"\n$n"+HIC+"����Ϊ$N"+HIC+"����,����������������ƻ�ľ�ɢ���裡\n"NOR,me,target);
                                        message_vision(HIR"\n����ƻ�Ʈ��֮���������ֹ�����$n"+HIR+"���Ծ���ģ�£�\n"NOR,me,target);
                                        COMBAT_D->do_attack(target, target, target->query_temp("weapon"));
                                        target->set("last_damage_from", me);
                                       	message_vision(HIY"\n$N"+HIY+"�ĺ���أ�����һ������$n\n"NOR, me,target);    
					damage = COMBAT_D->do_attack(me, target, weapon);
                                       	if (damage > 0 && skill > 349)
                                        {
                                               	message_vision(HIC"\n$n"+HIC+"��ǰ�������������뾡������ƻ𡣺�Ȼ�䣬����ƻ�û�������\n"NOR,me,target);
                                               	message_vision(HIC"\n$n"+HIC+"��Ȼ�����ξ�������ϸ��ĥ����ǰǧ����$n"+HIC+"֮ǰ��������\n"NOR,me,target);
                                               	message_vision(HIY"\n$N"+HIY+"���н���Ȼ��������֮�⣬��������$n\n"NOR, me,target);
                                               	message_vision(WHT"\n$n"+WHT+"ֻ����â��Ŀ��ȴ�������������ѣ�\n"NOR, me,target);
                                                damage = COMBAT_D->do_attack(me, target, weapon);
                                                if (damage > 0)
                                                {
                                                       	message_vision(HIC"\n$n"+HIC+"�Ѿ�������...\n"NOR,me,target);
                                                        target->receive_damage("sen", damage, me);
                                                }
	                                        else 
	                                        {
	                                                message_vision(HIC"\n��Ȼһ����紵��������ƻ�ͣ��˸��$n"+HIC+"��Ȼ���ѣ����Ǵ����죡\n"NOR,me,target); 
	                                                target->receive_damage("sen", 100, me);
	                                        }
	                              	}
					else
		                        {
		                        	message_vision(HIC"\n��Ȼ�ƻ�һ�٣�ԭ��$N"+HIC+"����ǰ��������������Ȼ���ˣ�\n"NOR,me,target);        
		                                message_vision(HIM"\n$N"+HIM+"�����ľ�����ȻһЦ��$n"+HIM+"����һ����$N"+HIM+"����ӽ�������\n"NOR,me,target);
		                                COMBAT_D->do_attack(me, target, weapon);
					}
				}
		                else
		                {
		                	message_vision(HIC"\n��Ȼ��ɫ�ƻ�ҡ�ڲ��������Ʋ�Ը����ɫ�ƻ�ͬ��һ��յ֮�У�\n"NOR,me,target);   
		                        message_vision(HIM"\n$N"+HIM+"ֻ��ͣ�½��裬���Ͼ��ǰ�����ɫ��$n"+HIM+"����һ㶣�$N"+HIM+"����ӽ�ǿ����\n"NOR,me,target);
					COMBAT_D->do_attack(me, target, weapon);
				}
			}
	                else
	                {
	                        message_vision(HIC"\n��Ȼ�������峪����Ȼ�ֶ�����ɫ���磬��ɫ����Ŭ������ȴ���������죡\n"NOR,me,target);      
	                       	message_vision(HIM"\n$N"+HIM+"ͻȻͣ�£������ڵ�ͷ˼�����ĵ����壬$n"+HIM+"����һ㶣�$N"+HIM+"����ӽ��͹���\n"NOR,me,target);
	                        COMBAT_D->do_attack(me, target, weapon);
	                }
        	}
	        else
	        {
	               	message_vision(HIC"\n$n"+HIC+"����һ����ԭ������ƣ���һ�ž޴�ķ���֮�ϣ�\n"NOR,me,target); 
	                message_vision(HIM"\n$N"+HIM+"ͣ�˽���,����һ��$n"+HIM+"����һ����$N"+HIM+"����ӽ��ɹ���\n"NOR,me,target);
	                COMBAT_D->do_attack(me, target, weapon);
	        }
   	}
	else
	{
		message_vision(HIC"\n$n"+HIC+"�󺰣���ϼ����ϼ˽���磬����ʲô���ģ���\n"NOR,me,target);
		message_vision(HIM"\n$N"+HIM+"���ĵؿ���$n"+HIM+"һ�ۣ��������˺�û��ˮ׼��$n"+HIM+"�����ƣ�$N"+HIM+"�Ѿ��ӽ����˹�ȥ��\n"NOR,me,target);
	      	COMBAT_D->do_attack(me, target, weapon);
	}
        target->add_temp("apply/dodge",extra/5);
        target->add_temp("apply/parry",extra/5);
        me->add_temp("apply/attack",-extra/5);
    	me->add_temp("apply/damage",-extra/5);
        if ((target->query("kee") < 0 || !living(target)) && !random(5))
	{
		str=target->name()+HIM+"��"+me->name()+HIM+"����˿�ش�"HIY"������ͬо��"NOR+HIM"ɱ���ˣ���˵"+target->name()+HIM+"��ʬ�徹Ȼ�ǰ��ϰ��࣡";
                message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
         me->set_temp("xin_end",time());
         return 1;
}
