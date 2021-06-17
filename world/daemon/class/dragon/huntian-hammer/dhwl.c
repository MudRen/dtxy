
// dhwl.c
//write by yeahsi
//yeahsi@21cn.com

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void check(object me, object target, object weapon);
void remove_effect(object me);

int perform(object me, object target)
{
        int skill, skill_hammer;
	string msg;
	object weapon;
        
        skill = me->query_skill("dragonforce",1);
	skill_hammer = me->query_skill("hammer");
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ������������\n");

        if(!me->is_fighting())
               return notify_fail("����������ֻ����ս����ʹ�ã�\n");
        
        if( skill < 100 )  return notify_fail("��������ķ���Ϊ������\n");
	if (me->query_temp("dhwl") && time()-(int)me->query_temp("dhwl_end") < 30)
		return notify_fail("���Ѿ���ʩչ�����������ˡ�\n");//�������30�뻹��״̬��֤�����ǿ�ס��
               
        if( (int)me->query("force") < skill_hammer / 3 )
		return notify_fail("�������������\n");
 	msg = HIC "$N��ת�����ķ������λ���һ�Ű����ƺ�һ�������ڿն���\n" NOR;
        me->add("force", -skill_hammer/5);
	me->set_temp("dhwl_end", time());
        me->set_temp("dhwl", 1);
	weapon = me->query_temp("weapon");
	message_vision(msg, me, target);
        call_out("check", 1, me,target, weapon);
        return 1;
}


void check(object me, object target, object weapon)
{
	int damage, count, weapon_damage;
	string msg, fail_msg, str;
	if(!me) return;
	me->add_temp("dhwl",1);
	count = me->query_temp("dhwl");
	if(me->query_skill("dragonforce",1) < 60 + count * 20)//count >= 2
	{
		remove_effect(me);
		return;
	}
    	if(!target || !weapon || count > 10)
	{
		remove_effect(me);
		return;
	}
    	if(!me->is_fighting())
	{
		remove_effect(me);
		return;
	}
        if(!present(target->query("id"), environment(me)) || !me->is_fighting(target))
	{
		remove_effect(me);
		return;
	}
	weapon_damage = weapon->query("weapon_prop/damage");
	switch (count)
	{
		case 10:
		{
	        	msg = HIC "\n$N����һ���죬�������ǿ�Ե�������ͻȻ���Լ����һ��������Ϊ����Ϊ��ֻ��ͷ����\n" NOR;
			msg += CYN "���ܻ�Ϊ��ʵ����$N����󺣻Ӷ�" + weapon->name() + CYN "Ҫ��$n���飡\n" NOR;
			fail_msg = HIG "$n��Ȼ����ˣ��ⴿ������ʹȻ��\n" NOR;
			break;
		}
		case 9:
		{
	        	msg = HIC "\n$Nͻ��������ת�����޷�ͻ�ƣ�������Ŀ��˼��Ȼ�����ڱ���˫Ŀ��һ˲����ʶ���۲��Ӷ����ڸεĵ���\n" NOR;
			msg += CYN "����������������" + weapon->name() + CYN "�Ƴ����ڴ󺣣�Ҫ��$n��û��\n" NOR;
			fail_msg = HIG "$n��Ϊ���Ӳ������һ����\n" NOR;
			break;
		}
		case 8:
		{
	        	msg = HIC "\n$N��ƽ�����������������಻�����룻�����Ŷ�����������������������������һ�㡣\n" NOR;
			msg += weapon->name() + CYN "�ϴ��������ĺ��������纣����ϯ��$n��\n" NOR;
			fail_msg = HIG "$n���Ǽᶨ����Ϊ��������һ����\n" NOR;
			break;
		}
		case 7:
		{
	        	msg = HIC "\n$N��ס��Ϣ����ת�����ڷμ䡣���������Ƴ�����Ȼ�ﵽ�˱ǲ�������ڷεľ��硣\n" NOR;
			msg += weapon->name() + CYN "���������˷���֮��������ͷ������$n��\n" NOR;
			fail_msg = HIG "$n�����Ͻ���˿�����ң�����һ����\n" NOR;
			break;
		}
		case 6:
		{
	        	msg = HIC "\n$N���������ķ����ԣ��಻���������ġ���æ����������������������һƬ���顣\n" NOR;
			msg += weapon->name() + CYN "���������ƴ󣬴��ž�������$n��\n" NOR;
			fail_msg = HIG "$n˳�����ˣ��������һ����\n" NOR;
			break;
		}
		case 5:
		{
	        	msg = HIC "\n$N�����ڵ���֮������ȫ������žž���죬��ת����ֱ���ζ����̲�ס������Х��\n" NOR;
			msg += weapon->name() + CYN "��Ӧ��Х��ֱ��$n��\n" NOR;
			fail_msg = HIG "$n���Ϻ��ˣ����Ƕ������һ����\n" NOR;
			break;
		}
		case 4:
		{
		        msg = HIC "\n$NĬ�������ķ�����֫����������Ƣ������δ����ȴֻ���������ڵ������������\n" NOR;
			msg += CYN "$N��" + weapon->name() + CYN "��ú������죬��������$n����Ҫ����\n" NOR;
			fail_msg = HIG "$n����ӭս�����в��У�����$N��һ����\n" NOR;
			break;
		}
		case 3:
		{
	        	msg = HIC "\n$N�������񣬰���������ϥ������������������ת�������ޱȡ�\n" NOR;
			msg += CYN "$N�������ɣ�" + weapon->name() + CYN "�Ե���ĽǶ�����$n��\n" NOR;
			fail_msg = HIG "$nȴ�������������ɶ������һ����\n" NOR;
			break;
		}
		case 2:
		{
	        	msg = HIC "\nת˲��$NͻȻ�������������죬���ϸ��ֳ�����������\n" NOR;
			msg += CYN "$N�������ǣ�һ������$n��\n" NOR;
			fail_msg = HIG "˭��$n������������������һ����\n" NOR;
			break;
		}
	}
	message_vision(msg, me, target);
	if(random(me->query("combat_exp")) > target->query("combat_exp") / count || !living(target))
	{
		damage = weapon_damage * count + me->query_skill("hammer") + me->query_str();
		damage -= target->query_temp("apply/armor");
		if(damage < weapon_damage * count / 2)
			damage = weapon_damage * count / 2;
		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage / 2, me);
		message_vision(COMBAT_D->damage_msg(damage, "����"), me, target);
		COMBAT_D->report_status(target, 1);
		if ((target->query("eff_kee") <= 0 || !living(target)) && !random(5))
                {
			str=target->name() + HIM"����" + me->name() + HIM"�ġ�������������" + me->name() + HIM"���������£���ʱ��Ѫ������"NOR;
			message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
		}
	}
	else
	{
		message_vision(fail_msg, me, target);
	}
	call_out("check", 1 + random(2), me,target,weapon);
}


void remove_effect(object me)
{
        if(!me || !me->query_temp("dhwl")) return;
        remove_call_out("check");
	remove_call_out("remove_effect");
        tell_object(me, CYN"������һ�ɣ�ͣ�ˡ�����������\n"NOR);
        me->delete_temp("dhwl");
	me->start_busy(1);
}


