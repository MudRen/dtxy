//盘丝洞最终pfm
//2004-1-6 by kryos //thank violet's describes  huarong 2004/1
//rewrited for dtxy2004 by huarong 2004/1
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit SSERVER;

int get_current_day_phase();
nosave mapping *day_phase = NATURE_D->query_day_phase();

int perform(object me, object target)
{
        string msg,kind,dodge_skill,str;
        int damage, qin,i,k,maxhit,myexp,youexp,ratio,skill;
        int chixinjian,qingxiajian,yinsuojinling,lanhuashou,jiuyinxinjing,pansidafa;
        int phase = get_current_day_phase();
        object weapon = me->query_temp("weapon");
        int cd = 10;
        //if(!wizardp(me))
        //	return notify_fail("巫师正在测试"+HIW+"「风华乱舞」"+NOR+"。。。\n");
      	if(!me->query("qingyun_known"))
           	return notify_fail("你还没有学会"+HIW+"「风华乱舞」"+NOR+"。。。\n");
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail(HIW+"「风华乱舞」"+NOR+"只能在战斗中使用。\n");

        if((int)me->query_skill("unarmed", 1) < 200 ||
           (int)me->query_skill("sword", 1) < 200 ||
           (int)me->query_skill("whip",1) < 200)
                return notify_fail("你的基本功夫学的不到家，无法使用"+HIW+"「风华乱舞」"+NOR+"!\n");

        if((int)me->query_skill("lanhua-shou", 1) < 200 ||
           (int)me->query_skill("qingxia-jian", 1) < 200 ||
           (int)me->query_skill("yinsuo-jinling",1) < 200||
           (int)me->query_skill("jiuyin-xinjing",1) < 200||
           (int)me->query_skill("pansi-dafa",1) < 200||
           (int)me->query_skill("chixin-jian",1) < 200)
                return notify_fail("你盘丝洞的功夫学的不到家，无法使用"+HIW+"「风华乱舞」"+NOR+"!\n");

        if((int)me->query_skill("qin",1) < 200)
                return notify_fail("你不通音律，无法使用"+HIW+"「风华乱舞」"+NOR+"!\n");

        //if(weapon->query("id")!="yinsuo jinling")
        //        return notify_fail("除了银索金铃，好像还没有听说什么武器可以与五韵相通呀！");
        if(me->query("family/family_name")!="盘丝洞")
                return notify_fail(HIW"「风华乱舞」"+NOR+"只有盘丝洞弟子才可以用！\n");
        if( (int)me->query("max_force") < 2000 )
                return notify_fail("你的内力修为太弱，根本使不出"+HIW+"「风华乱舞」"+NOR+"！\n");
        if( (int)me->query("force") < 2000 )
                return notify_fail("你的真气不够！\n");
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("fenghua_end") < cd )
                return notify_fail("绝招用多就不灵了！\n");

        qin = me->query_skill("qin",1);

        if(random(target->query_per())<=me->query("per") && (phase<0 || phase>5))
        {
                kind = CYN;
                msg = HIC"\n$N"+HIC+"合着清脆的金铃，轻声念了一句：长天净，绛河清浅，皓月蝉娟。\n" NOR;
                msg = msg + HIC"清风倏起，天空立时明净了许多，月华仿佛也越来越浓了！\n"NOR;
                msg = msg + HIC"$n"+HIC+"听得风似丝竹，见得羽衣轻舞，月华中容颜绝世，心便醉了。\n\n"NOR;
                msg = msg + HIC"$N"+HIC+"一声清啸，$n"+HIC+"眼前月华大盛，不禁慌了手脚，$N"+HIC+"展开了强大的攻势。\n\n"NOR;
                str = me->name() + HIM"使出盘丝洞绝学" + HIC"「风华乱舞」"NOR + HIM"，" + target->name() + HIM"陶醉在" + HIC"「影月」"+HIM+"的意境之中，飘然仙去！";
        }
        else if(random(target->query_per())<=me->query("per") && phase>=0 && phase<=6)
        {
                kind = YEL;
                msg = HIY"\n$N"+HIY+"合着欢快的金铃，轻声念了一句：云想衣裳花想容，春风拂槛露华浓。\n" NOR;
                msg = msg + HIY"舞动的金铃循着欢快的轨迹折射阳光，$N的身形渐渐消失在一片金光之中！\n"NOR;
                msg = msg + HIY"$n"+HIY+"觉得那金光虽然明亮却不刺目，耳边铃声悦耳，心中杀意渐消。\n\n"NOR;
                msg = msg + HIY"$N"+HIY+"一声清啸，$n"+HIY+"眼前金光大盛，不禁慌了手脚，$N"+HIY+"展开了强大的攻势。\n\n"NOR;
                str = me->name() + HIM"使出盘丝洞绝学" + HIY"「风华乱舞」"NOR + HIM"，" + target->name() + HIM"在" + HIY"「阳光」"+HIM+"的意境之中飘然仙去！";
        }
        else
        {
                kind = BLU;
                msg = HIB"\n$N"+HIB+"合着忧伤的金铃，轻声念了一句：七月七日长生殿，夜半无人私语时。\n"NOR;
                msg = msg + HIB"刹那间，天空中阴云聚合，不一会便下起了密密细雨！\n"NOR;
                msg = msg + HIB"$n"+HIB+"只觉得四周突然鬼气森然，细听雨声，竟如夜半冤魂血泣，立时打了几个冷战。\n\n"NOR;
                msg = msg + HIB"$N"+HIB+"一声鬼啸，$n"+HIB+"被吓得胆战心惊，$N"+HIB+"展开了强大的攻势。\n\n"NOR;
                str = me->name() + HIM"使出盘丝洞绝学" + HIB"「风华乱舞」"NOR + HIM"，" + target->name() + HIM"在" + HIB"「妖雨」"+HIM+"的意境之中，被吓得魂飞魄散！";
        }
        message_vision(msg, me, target);
	if(me->query("qingyun_known") == 1)
		qin = qin * 3 / 2;
	else
		qin = qin * 3;
	target->add_temp("apply/dodge",-qin/4);
	target->add_temp("apply/parry",-qin/4);
	me->add_temp("apply/attack",qin/4);
    	me->add_temp("apply/damage",qin/4);
      	message_vision(kind + BLINK + "剑有痴心醉\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "自在青霞舞\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "幽谷兰花静\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "心中盘丝结\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "九阴由此成\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "宫商角徵羽\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "风华曲中求\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	target->add_temp("apply/dodge",qin/4);
	target->add_temp("apply/parry",qin/4);
	me->add_temp("apply/attack",-qin/4);
    	me->add_temp("apply/damage",-qin/4);
    	me->start_busy(2);
    	me->set_temp("fenghua_end",time());
    	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )
		message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
        return 1;
}

int get_current_day_phase() {
    mixed *local = localtime(time()*60);
    int t = local[2] * 60 + local[1];
    int i;
    for (i=0; i<sizeof(day_phase); i++)
        if (t>=day_phase[i]["length"])
            t -= (int)day_phase[i]["length"];
        else
            break;
    return (i==0 ? sizeof(day_phase)-1 : i-1);
}
