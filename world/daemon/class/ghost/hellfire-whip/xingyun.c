//��������
//by lestat 2001��һ


#include <ansi.h>

inherit SSERVER;
int perform(object me, object target)
{
    object weapon;
	string who1, who2;
    int damage, lvl, r_lvl, count, form, skill, i;
    string msg;
        if( !target ) target = offensive_target(me);
        
        if( !me->query_skill("hellfire-whip", 1) )
                return notify_fail("�㲻�����������󷨡�\n");
if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С�������������\n");
        if( skill > 300 ) skill=300;
        if(me->query("family/family_name") != "���޵ظ�" )
                return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á�����������?\n");
        if(!me->is_fighting(target))
                return notify_fail("������������ֻ����ս����ʹ�ã�\n");
        if((int)me->query("max_force") < 1000 )
                return notify_fail("�������������\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("hellfire-whip", 1) < 100)
                return notify_fail("����һ�޼��𻹲�����С���߻���ħ��\n");               
        if (me->query_skill_mapped("force")!="tonsillit")
                return notify_fail("�������������������������ʹ�á�\n"); 
                if( time()-(int)me->query_temp("xingyun_end") < 5 )
                return notify_fail("�����ö�Ͳ����ˣ�\n"); 
            me->delete("env/brief_message");
            target->delete("env/brief_message");
    skill = (int)me->query_skill("hellfire-whip", 1);
	lvl = skill/20;
	r_lvl = 3+random(lvl);
if( r_lvl > 9) r_lvl = 9;
	//if( r_lvl < 1) r_lvl = 1;
	count = me->query_str();
	message_vision(HIB"\n$Nʹ����ڤ��ѧ�������������г��ޱ���,�������,˲�����������һ������,$n�Ĺ������������ء�\n"NOR,me,target);
	tell_object(target, HIW"��Ȼ���㷢����һ����ֵ���������Ϯ��,����һ���ƺ��Ѿ���ʼ���ᣡ\n"NOR);
 if (random(me->query("force",1)) > 4*target->query("force",1)/5 )
        {
                target->start_busy(random(3));                
                damage = skill/2 + r_lvl*target->query("force_factor",1);                
                target->receive_damage("kee", damage,me);
                target->receive_wound("kee", damage,me);
                me->add("force", -damage/5);
				//msg = CYN "$NĬ���񹦣�ʹ�����������󷨡�\n"NOR;
	        	msg = HIB "�����ֽ�$n������ȫ��������ȥ��\n" NOR;                
                if( damage < 70 )
                        msg += HIY"���$n�ܵ�$N�����������ƺ�һ����\n"NOR;
        	else if( damage < 100 )
                       msg += HIY"���$n��$N���������𣬡��١���һ������������\n"NOR;
        	else if( damage < 150 )
                       msg += RED"���$n��$N������һ���ؿ������ܵ�һ���ش�����������������\n"NOR;
                else
                       msg += HIR"���$n��$N������һ����ǰһ�ڣ���һ������һ���ɳ�ȥ�ü���Զ��\n"NOR;
                message_vision(msg, me, target);
                COMBAT_D->report_status(target);
        }
else if((random(me->query("combat_exp")) > (int)target->query("combat_exp")/5 ))
        {
		tell_object(target, HIG"�����������ƺ��й����������������ĳ��о�Ȼ���˻��������Լ���\n"NOR);
		message("vision", HIW"\n" + target->name() + "��Ȼ����ħһ�㣬���л����Լ���\n\n"NOR, environment(me), target);
		for(i = 0; i < r_lvl; i++)
		COMBAT_D->do_attack(target, target, target->query_temp("weapon") );
		target->set_temp("last_damage_from",me);
		me->add("force", -300);
		}

     else
     {
     	message_vision(CYN"\n$n�����ڹ������������֣��ǹ���ֵ�����ͬʱ��ʧ�ˡ�\n"NOR, me, target);
     	if( me->query("lunhui_zhuanshi") < 4 )
     	{
     		if( me->query("lunhui_zhuanshi") > 1 )
  			me->start_busy(1);
  		else
  			me->start_busy(2);
  	}
     }
        me->set_temp("xingyun_end",time());
        return 1;
}

