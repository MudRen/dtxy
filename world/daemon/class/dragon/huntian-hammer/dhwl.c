
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
                return notify_fail("你要对谁施展「大海无量」？\n");

        if(!me->is_fighting())
               return notify_fail("「大海无量」只能在战斗中使用！\n");
        
        if( skill < 100 )  return notify_fail("你的龙神心法修为不够。\n");
	if (me->query_temp("dhwl") && time()-(int)me->query_temp("dhwl_end") < 30)
		return notify_fail("你已经在施展「大海无量」了。\n");//如果超过30秒还有状态，证明就是卡住了
               
        if( (int)me->query("force") < skill_hammer / 3 )
		return notify_fail("你的内力不够。\n");
 	msg = HIC "$N运转龙神心法，身形化作一团白雾，似乎一条蛟龙腾空而起。\n" NOR;
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
	        	msg = HIC "\n$N运气一周天，浑身充满强霸的力道。突然间脑际灵光一闪，气化为神，神化为虚只冲头顶。\n" NOR;
			msg += CYN "四周化为真实海域，$N龙归大海挥动" + weapon->name() + CYN "要将$n砸碎！\n" NOR;
			fail_msg = HIG "$n竟然躲过了，这纯是运气使然。\n" NOR;
			break;
		}
		case 9:
		{
	        	msg = HIC "\n$N突觉内力运转周身无法突破，不禁闭目沉思，然而就在闭上双目的一瞬间意识到眼不视而魂在肝的道理。\n" NOR;
			msg += CYN "海潮声振聋发聩，" + weapon->name() + CYN "似沉浮于大海，要将$n淹没！\n" NOR;
			fail_msg = HIG "$n修为深厚，硬抗了这一锤。\n" NOR;
			break;
		}
		case 8:
		{
	        	msg = HIC "\n$N心平气静，对外界的嘈杂亦不听不想；耳不闻而精在肾，沉身运气，内力更高了一层。\n" NOR;
			msg += weapon->name() + CYN "上传来清晰的海潮声，如海潮般席卷$n！\n" NOR;
			fail_msg = HIG "$n心智坚定，不为所惑，再破一锤。\n" NOR;
			break;
		}
		case 7:
		{
	        	msg = HIC "\n$N屏住气息，运转内力于肺间。呼吸均匀悠长，以然达到了鼻不香而魄在肺的境界。\n" NOR;
			msg += weapon->name() + CYN "上隐隐起了风浪之声，如浪头般砸向$n！\n" NOR;
			fail_msg = HIG "$n法度严谨，丝毫不乱，再破一锤。\n" NOR;
			break;
		}
		case 6:
		{
	        	msg = HIC "\n$N想起龙神心法所言：舌不吟而神在心。连忙收声运气，但觉得心灵中一片空灵。\n" NOR;
			msg += weapon->name() + CYN "声势愈发浩大，带着劲风砸向$n！\n" NOR;
			fail_msg = HIG "$n顺势再退，躲过了这一锤。\n" NOR;
			break;
		}
		case 5:
		{
	        	msg = HIC "\n$N将沉于丹田之力带行全身，身上啪啪连响，运转自如直冲任督，忍不住纵声长啸。\n" NOR;
			msg += weapon->name() + CYN "呼应着啸声直击$n！\n" NOR;
			fail_msg = HIG "$n不断后退，终是躲过了这一锤。\n" NOR;
			break;
		}
		case 4:
		{
		        msg = HIC "\n$N默念龙神心法，四肢不动而意在脾，人虽未动，却只觉内力沉于丹田，力量倍增。\n" NOR;
			msg += CYN "$N把" + weapon->name() + CYN "舞得呼呼作响，锤锤不离$n周身要害！\n" NOR;
			fail_msg = HIG "$n凝神迎战，见招拆招，破了$N这一锤。\n" NOR;
			break;
		}
		case 3:
		{
	        	msg = HIC "\n$N收敛心神，把内力运至膝间跳环，但觉内力运转间身轻无比。\n" NOR;
			msg += CYN "$N仗着灵巧，" + weapon->name() + CYN "以刁钻的角度砸向$n！\n" NOR;
			fail_msg = HIG "$n却更加灵活，轻松松松躲过了这一锤。\n" NOR;
			break;
		}
		case 2:
		{
	        	msg = HIC "\n转瞬间$N突然周身骨骼格格做响，面上浮现出阵阵青气。\n" NOR;
			msg += CYN "$N气力大涨，一锤砸向$n！\n" NOR;
			fail_msg = HIG "谁想$n力气更大，生接下了这一锤。\n" NOR;
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
		message_vision(COMBAT_D->damage_msg(damage, "砸伤"), me, target);
		COMBAT_D->report_status(target, 1);
		if ((target->query("eff_kee") <= 0 || !living(target)) && !random(5))
                {
			str=target->name() + HIM"中了" + me->name() + HIM"的「大海无量」，在" + me->name() + HIM"的内力震荡下，顿时吐血身亡！"NOR;
			message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
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
        tell_object(me, CYN"你真气一松，停了「大海无量」。\n"NOR);
        me->delete_temp("dhwl");
	me->start_busy(1);
}


