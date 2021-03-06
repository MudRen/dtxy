// combatd.c
// 03062006 emotion: fixed possible overflow issue

//#pragma optimize

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
#include "/cmds/std/valid_kill.h"


inherit F_DBASE;

int victim_lose(object killer,object victim,string killerid);
void victim_penalty(object victim);
int nk_gain(object killer, object victim);
string chinese_daoxing(int gain);

int check_family(string fam);

string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
//this mapping indicates whether this family class is
//xian or yao.
mixed *wuxing = ({
			({"gold_attack",0}),
			({"water_attack",1}),
			({"wood_attack",2}),
			({"fire_attack",3}),
			({"earth_attack",4}),
		 });
mapping family=(["方寸山三星洞":1,
                 "蜀山派":1,
				 "水月宫":1,
				 "南海普陀山":1,
                 "五庄观":1,
                 "阎罗地府":-1,
                 "月宫":1,
                 "东海龙宫":1,
                 "大雪山":-1,
                 "陷空山无底洞":-1,
                 "盘丝洞":-1,
                 "将军府":1,
                 "三界散仙":-1,
                 "昆仑山玉虚洞":1,
                 "火云洞":-1,
/*
				 "南海普陀山":1,
                 "将军府":1,
                 "五庄观":1,
                 "阎罗地府":0,
                 "月宫":0,
                 "东海龙宫":0,
                 "龙宫":0,
                 "大雪山":-1,
                 "翠云山芭蕉洞":-1,
                 "陷空山无底洞":-1,
                 "乱石山碧波潭":-1,
                 "火云洞":-1,
*/
]);

string *guard_msg = ({
    CYN "$N注视着$n的行动，企图寻找机会出手。\n" NOR,
    CYN "$N正盯着$n的一举一动，随时准备发动攻势。\n" NOR,
    CYN "$N缓缓地移动脚步，想要找出$n的破绽。\n" NOR,
    CYN "$N目不转睛地盯着$n的动作，寻找进攻的最佳时机。\n" NOR,
    CYN "$N慢慢地移动着脚步，伺机出手。\n" NOR,
});

string *catch_hunt_msg = ({
    HIW "$N和$n仇人相见份外眼红，立刻打了起来！\n" NOR,
    HIW "$N对着$n大喝：「可恶，又是你！」\n" NOR,
    HIW "$N和$n一碰面，二话不说就打了起来！\n" NOR,
    HIW "$N一眼瞥见$n，「哼」的一声冲了过来！\n" NOR,
    HIW "$N一见到$n，愣了一愣，大叫：「我宰了你！」\n" NOR,
    HIW "$N喝道：「$n，我们的帐还没算完，看招！」\n" NOR,
    HIW "$N喝道：「$n，看招！」\n" NOR,});

string *winner_msg = ({
    CYN "\n$N哈哈大笑，说道：承让了！\n\n" NOR,
    CYN "\n$N双手一拱，笑着说道：承让！\n\n" NOR,
    CYN "\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR,
    CYN "\n$n脸色微变，说道：佩服，佩服！\n\n" NOR,
    CYN "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR,
    CYN "\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
});

void create()
{
    seteuid(getuid());
    set("name", "战斗精灵");
    set("id", "combatd");
}

string damage_msg(int damage, string type)
{
    string str;

//  return "造成 " + damage + " 点" + type + "。\n";

    if( damage == 0 ) return "结果没有造成任何伤害。\n";

    switch( type ) {
    case "擦伤":
    case "抓伤":
    case "割伤":
        if( damage < 10 ) return "结果只是轻轻地划破$p的皮肉。\n";
        else if( damage < 20 ) return "结果在$p$l划出一道细长的血痕。\n";
        else if( damage < 40 ) return "结果「嗤」地一声划出一道伤口！\n";
        else if( damage < 80 ) return "结果「嗤」地一声划出一道血淋淋的伤口！\n";
        else if( damage < 160 ) return "结果「嗤」地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
        else return "结果只听见$n一声惨嚎，$p的$l被划出一道深及见骨的可怕伤口！\n";
        break;
    case "砍伤":
    case "劈伤":
        if( damage < 10 ) return "结果只是在$n的皮肉上碰了碰，跟蚊子叮差不多。\n";
        else if( damage < 20 ) return "结果在$n$l砍出一道细长的血痕。\n";
        else if( damage < 40 ) return "结果「噗嗤」一声劈出一道血淋淋的伤口！\n";
        else if( damage < 80 ) return "结果只听「噗」地一声，$n的$l被劈得血如泉涌，痛得$p咬牙切齿！\n";
        else if( damage < 160 ) return "结果「噗」地一声砍出一道又长又深的伤口，溅得$N满脸鲜血！\n";
        else return "结果只听见$n一声惨嚎，$p的$l被劈开一道深及见骨的可怕伤口！\n";
        break;
    case "枪伤":
    case "刺伤":
        if( damage < 10 ) return "结果只是轻轻地刺破$p的皮肉。\n";
        else if( damage < 20 ) return "结果在$p$l刺出一个创口。\n";
        else if( damage < 40 ) return "结果「噗」地一声刺入了$n$l寸许！\n";
        else if( damage < 80 ) return "结果「噗」地一声刺进$n的$l，使$p不由自主地退了步！\n";
        else if( damage < 160 ) return "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉模糊的血窟窿！\n";
        else return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！\n";
        break;
    case "筑伤":
        if( damage < 10 ) return "结果只是轻轻地一触，在$n的皮肤上留下一点白痕。\n";
        else if( damage < 20 ) return "结果在$p的$l留下几道血痕。\n";
        else if( damage < 40 ) return "结果一下子筑中，$n的$l顿时出现几个血孔！\n";
        else if( damage < 80 ) return "结果一下子筑中，$n立刻血流如注！\n";
        else if( damage < 120 ) return "结果「哧」地一声，$n顿时鲜血飞溅！\n";
        else if( damage < 160 ) return "结果这一下「哧」地一声，$n被筑得浑身是血！\n";
        else return "结果「哧」重重地砸中，$n被筑得千疮白孔，血肉四处横飞！\n";
        break;
    case "掌伤":
    case "拳伤":
    case "瘀伤":
        if( damage < 10 ) return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
        else if( damage < 20 ) return "结果在$p的$l造成一处瘀青。\n";
        else if( damage < 40 ) return "结果一击命中，$n的$l登时肿了一块老高！\n";
        else if( damage < 80 ) return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n";
        else if( damage < 120 ) return "结果「砰」地一声，$n退了两步！\n";
        else if( damage < 160 ) return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n";
        else if( damage < 240 ) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
        else return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！\n";
        break;
    case "撞伤":
    case "砸伤":
        if( damage < 10 ) return "结果只是轻轻地碰到，等于给$n搔了一下痒。\n";
        else if( damage < 20 ) return "结果在$p的$l砸出一个小臌包。\n";
        else if( damage < 40 ) return "结果砸个正着，$n的$l登时肿了一块老高！\n";
        else if( damage < 80 ) return "结果砸个正着，$n闷哼一声显然吃了不小的亏！\n";
        else if( damage < 120 ) return "结果「砰」地一声，$n疼得连腰都弯了！\n";
        else if( damage < 160 ) return "结果这一下「轰」地一声砸得$n眼冒金星，差一点摔倒！\n";
        else if( damage < 240 ) return "结果重重地砸中，$n眼前一黑，「哇」地一声吐出一口鲜血！\n";
        else return "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！\n";
        break;
    case "震伤":
    case "内伤":
        if( damage < 20 ) return "结果在$n身上一触即逝，等于给$n搔了一下痒。\n";
        else if( damage < 40 ) return "结果$n晃了一晃，吃了点小亏。\n";
        else if( damage < 80 ) return "结果$n气息一窒，显然有点呼吸不畅！\n";
        else if( damage < 120 ) return "结果$n体内一阵剧痛，看起来内伤不轻！\n";
        else if( damage < 160 ) return "结果「嗡」地一声$n只觉得眼前一黑，双耳轰鸣不止！\n";
        else return "结果只听见「嗡」地一声巨响，$n「哇」地一声吐出一口鲜血，五脏六腑都错了位！\n";
        break;
        case "鞭伤":
        case "抽伤":
        if( damage < 10 ) return "结果只是在$n的皮肉上碰了碰，跟蚊子叮差不多。\n";
        else if( damage < 20 ) return "结果在$n$l抽出一道轻微的紫痕。\n";
        else if( damage < 40 ) return "结果「啪」地一声在$n$l抽出一道长长的血痕！\n";
        else if( damage < 80 ) return "结果只听「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n";
        else if( damage < 160 ) return "结果「啪」地一声爆响！这一下好厉害，只抽得$n皮开肉绽，血花飞溅！\n";
        else return "结果只听见$n一声惨嚎，$w重重地抽上了$p的$l，$n顿时血肉横飞，十命断了九条！\n";
        break;
    default:
        if( !type ) type = "伤害";
        if( damage < 10 ) str =  "结果只是勉强造成一处轻微";
        else if( damage < 20 ) str = "结果造成轻微的";
        else if( damage < 30 ) str = "结果造成一处";
        else if( damage < 50 ) str = "结果造成一处严重";
        else if( damage < 80 ) str = "结果造成颇为严重的";
        else if( damage < 120 ) str = "结果造成相当严重的";
        else if( damage < 170 ) str = "结果造成十分严重的";
        else if( damage < 230 ) str = "结果造成极其严重的";
        else str =  "结果造成非常可怕的严重";
        return str + type + "！\n";
    }
}

string eff_status_msg(int ratio)
{
    if( ratio==100 ) return HIG "看起来气血充盈，并没有受伤。" NOR;
    if( ratio > 95 ) return HIG "似乎受了点轻伤，不过光从外表看不大出来。" NOR;
    if( ratio > 90 ) return HIY "看起来可能受了点轻伤。" NOR;
    if( ratio > 80 ) return HIY "受了几处伤，不过似乎并不碍事。" NOR;
    if( ratio > 60 ) return HIY "受伤不轻，看起来状况并不太好。" NOR;
    if( ratio > 40 ) return HIR "气息粗重，动作开始散乱，看来所受的伤着实不轻。" NOR;
    if( ratio > 30 ) return HIR "已经伤痕累累，正在勉力支撑着不倒下去。" NOR;
    if( ratio > 20 ) return HIR "受了相当重的伤，只怕会有生命危险。" NOR;
    if( ratio > 10 ) return RED "伤重之下已经难以支撑，眼看就要倒在地上。" NOR;
    if( ratio > 5  ) return RED "受伤过重，已经奄奄一息，命在旦夕了。" NOR;
    return RED "受伤过重，已经有如风中残烛，随时都可能断气。" NOR;
}

string status_msg(int ratio)
{
    if( ratio==100 ) return HIG "看起来充满活力，一点也不累。" NOR;
    if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
    if( ratio > 90 ) return HIY "看起来可能有些累了。" NOR;
    if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
    if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
    if( ratio > 40 ) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
    if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑着不倒下去。" NOR;
    if( ratio > 20 ) return HIR "看起来已经力不从心了。" NOR;
    if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
    return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}

//report_shen messages
string sen_status_msg(int ratio)
{
    if( ratio==100 ) return HIG "看起来头脑清醒，一点也不迷糊。" NOR;
    if( ratio > 90 ) return HIG "拍了拍自己的脑袋，似乎有点不太得劲。" NOR;
    if( ratio > 80 ) return HIY "看起来有些迷糊了。" NOR;
    if( ratio > 60 ) return HIY "的确有点迷糊了，但还辨得出东西南北。" NOR;
    if( ratio > 40 ) return HIR "两眼发直，口角流涎，神智开始混乱。" NOR;
    if( ratio > 20 ) return HIR "迷迷糊糊，摇摇晃晃，已经辨不出东西南北了。" NOR;
    if( ratio > 10 ) return RED "神智已经处在极度混乱中。" NOR;
    return RED "心智已经完全迷失，随时都有可能背过气去。" NOR;
}

varargs void report_status(object ob, int effective)
{
    if( effective )
        message_vision( "( $N" + eff_status_msg(
                   (int)ob->query("eff_kee") * 100 /(1+(int)ob->query("max_kee")) )
                   + " )\n", ob);
    else
        message_vision( "( $N" + status_msg(
                   (int)ob->query("kee") * 100/(1+(int)ob->query("max_kee")) )
                   + " )\n", ob);
}

varargs void report_sen_status(object ob, int effective)
{

    message_vision( "( $N" + sen_status_msg(
        (int)ob->query("sen") * 100 /(1+(int)ob->query("max_sen")) )
        + " )\n", ob);
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
varargs float skill_power(object ob, string skill, int usage)
{
    int status;
    float level, power;

    if( !living(ob) ) return 0;

    level = 0.0 + ob->query_skill(skill);  // put a leading 0.0 there is to let the compiler know this is a float
                                           // if don't do like this, there is a bug in compiler will use integer instead
                                           // float...

    switch(usage) {
        case SKILL_USAGE_ATTACK:
            level = 0.0 + ob->eff_skill_level(level, SKILL_USAGE_ATTACK);
            level = level + ob->query_temp("apply/attack");
            break;
        case SKILL_USAGE_DEFENSE:
            level = 0.0 + ob->eff_skill_level(level, SKILL_USAGE_DEFENSE);
            level = level + ob->query_temp("apply/defense");
            break;
    }

    if( !level ) return (float)ob->query("combat_exp") / 2;

    power = (level*level*level) / 3;
    if( (status = ob->query("max_sen")) > 0 )  {
        if ( power > 100000 )
           power = power / status * (int)ob->query("sen");
        else
           power = power * (int)ob->query("sen") / status;
    }

    power = power + ob->query("combat_exp");

//	tell_object(ob, "power " + power + "\n");

    return power;
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
    mapping my, your, action, victim_action;
    string limb, *limbs, result,fail_hit_msg,hit_ob_msg;
//    string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
    mixed foo;
    float ap, dp, pp, afp, vfp, mod_val, force_adj;   //afp: attacker->force power, vfp: victim->force power
    int damage, damage_bonus, defense_factor;
    int wounded = 0;

    if( !me || !objectp(me) || !victim || !objectp(victim) ) return 0;

    if( environment(me) != environment(victim) )
         return 0;

    my = me->query_entire_dbase();
    your = victim->query_entire_dbase();

    //
    // (1) Find out what action the offenser will take.
    //
    action = me->query("actions");
    if( !mapp(action) )
    {
    	me->reset_action();
        action = me->query("actions");
        if( !mapp(action) )
        {
            CHANNEL_D->do_channel( this_object(), "sys",sprintf("%s(%s): bad action = %O",
                    me->name(1), me->query("id"), me->query("actions", 1)));
            return 0;
        }
    }
    if (action["name"])
        me->set_temp("action_name",action["name"]);
    result = "\n" + action["action"] + "！\n";

    //取得me用什么兵器的数据
       if( objectp(weapon) )
       {
            if( weapon->query("use_apply_skill") )
                attack_skill = weapon->query("apply/skill_type");
            else
                attack_skill = weapon->query("skill_type");
        }
       else     attack_skill = "unarmed";

    limbs = victim->query("limbs");
    limb = limbs[random(sizeof(limbs))];

       //(2) 加上特殊内功的防御能力 added by yeahsi
       if ( victim->query_temp("jldl") && living(victim) )       //如果敌人运用了jldl,而且不是晕的
       {
       	    afp = skill_power(me, "force", SKILL_USAGE_ATTACK);
            if( afp < 1) afp = 1.0;
            vfp = skill_power(victim, "force", SKILL_USAGE_DEFENSE);
            if( vfp < 1 ) vfp = 1.0;
            mod_val = 0.0;
            mod_val = mod_val - random(25);
            if (!victim->query_temp("weapon")) mod_val = mod_val + 10;
            if( vfp > 1000000 )     mod_val = vfp / 100 * (mod_val + 100);
            else   mod_val = (mod_val + 100) * vfp / 100;
            if( mod_val < 1 ) mod_val = 1.0;
            force_adj=(afp + vfp) * random(1000000) / 1000000;
       }
       else {force_adj=1;mod_val=1;}


    //
    // (3) Fight!
    //     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
    //     AP and DP are greater than zero, so we always have chance to hit
    //     or be hit.
    //




        if ( force_adj < mod_val )
        {
        	foo = "/daemon/class/puti/wuxiangforce/jldl"->jldl_result(victim, me, mod_val, force_adj,action);
                result += foo;
                damage = RESULT_FORCE;
        }
        else
        {
        	//Prepare AP, DP for checking if hit.
                ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
    		if( ap < 1) ap = 1.0;

    		dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);

                if(living(victim))
                	dodge_skill = victim->query_skill_mapped("dodge");
                else
                	dodge_skill = 0;
                mod_val = 0.0;
    		if( dodge_skill )
    		{
    			victim_action = SKILL_D(dodge_skill)->query_action();
       			if( victim_action && victim_action["dodge_power"] )
          			mod_val = victim_action["dodge_power"];
    		}
    		if( victim->is_busy() ) dp = dp / 3;
    		if( dp < 1 ) dp = 1.0;

    		if( action["dodge"] )  mod_val = mod_val + action["dodge"];
    		if( dp > 1000000 )
       			mod_val = dp / 100 * (mod_val + 100);
    		else
       			mod_val = (mod_val + 100) * dp / 100;
    		if( mod_val < 1 ) mod_val = 1.0;

		if( (ap + dp) * random(1000000) / 1000000 < mod_val )
		{
			// Does the victim dodge this hit?

        		if( !dodge_skill )
        		{
        			dodge_skill = "dodge";
           			result += SKILL_D(dodge_skill)->query_dodge_msg(limb);
        		}
        		else
        		{
        			if( victim_action && victim_action["dodge_action"] )
              				result += victim_action["dodge_action"];
        			else
              				result += SKILL_D(dodge_skill)->query_dodge_msg(limb);
        		}

        		if( dp < ap && (!userp(victim) || !userp(me))
        			    && random(sizeof(victim->query_enemy())) < 4
                                    &&  random(your["sen"]*100/your["max_sen"]
                                        + victim->query_int() * victim->query_cps()) > 150 )
                        {
                        	your["combat_exp"] += 1 + random( victim->query_int() / 10 );
            			victim->improve_skill("dodge", 1 + random( victim->query_int() ) );
        		}

        		// This is for NPC only. NPC have chance to get exp when fail to hit.
        		if( (ap < dp) && !userp(me) )
        		{
        			if( random(me->query_int()) > 15 ) {
        			    my["combat_exp"] += 1 + random( me->query_int() / 10 );
            			me->improve_skill(attack_skill, 1 + random( me->query_int() ));
					}
        		}

        		damage = RESULT_DODGE;
		}
		else
		{
			//(4) Check if the victim can parry this attack.
               		if( victim->query_temp("weapon") )
               		{
               			pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
            			if( !weapon ) pp = pp * 2;
            			parry_skill = victim->query_skill_mapped("parry");
        		}
        		else
        		{
        			if( weapon ) pp = 0.0;
            			else pp = skill_power(victim, "unarmed", SKILL_USAGE_DEFENSE);
            			parry_skill = victim->query_skill_mapped("unarmed");
        		}

        		if( victim->is_busy() ) pp = pp / 3;
        		if( pp < 1 ) pp = 1.0;
        		mod_val = 0.0;
        		if( action["parry"] )
        			mod_val = 0.0 + action["parry"];
        		if( pp > 1000000 )
           			mod_val = pp / 100 * (mod_val + 100 );
        		else
           			mod_val = (mod_val + 100 ) * pp / 100;
        		if(mod_val < 1)  mod_val = 1.0;

        		if( (ap + pp)  * random(1000000) / 1000000 < mod_val )
        		{
        			//parry_skill = victim->query_skill_mapped("parry");
            			if( !parry_skill ) parry_skill = "parry";
			        // change to SKILL_D(parry_skill) after added parry msg to those
			        // martial arts that can parry.
			        // because of number of local variable limit, here use
			        // dodge_skill
            			dodge_skill = SKILL_D(parry_skill)->query_parry_msg(weapon);
            			if( dodge_skill )	result += dodge_skill;
            			else	result += SKILL_D("parry")->query_parry_msg(weapon);

            			if( pp < ap && (!userp(victim) || !userp(me))
            				    && random(sizeof(victim->query_enemy())) < 4
            			            &&  random(your["sen"]*100/your["max_sen"]
            			                + victim->query_int() * victim->query_cps()) > 150 )
            			{
            				your["combat_exp"] += 1 + random( victim->query_int() / 10 );
                			victim->improve_skill("parry", 1 + random( victim->query_int() ));
            			}
            			damage = RESULT_PARRY;
                	}
                	else
                	{
                		//  (5) We hit the victim and the victim failed to parry
                        	damage = me->query_temp("apply/damage");
            			damage = (damage + random(damage)) / 2;
			        if( action["damage"] )
                			damage += action["damage"] * damage / 100;

            			damage_bonus = me->query_str();

            			// Let force skill take effect.
            			if( my["force_factor"] && (my["force"] > my["force_factor"]) )
            			{
            				if( force_skill = me->query_skill_mapped("force") )
            				{
            					foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["force_factor"]);
            					if( stringp(foo) ) result += foo;
                    				else if( intp(foo) ) damage_bonus += foo;
                			}
            			}

            			if( action["force"] )
                			damage_bonus += action["force"] * damage_bonus / 100;

            			if( martial_skill = me->query_skill_mapped(attack_skill) )
            			{
            				foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
                			if( stringp(foo) ) result += foo;
                			else if(intp(foo) ) damage_bonus += foo;
            			}

            			// Let weapon or monster have their special damage.
            			if( weapon )
            			{
            				foo = weapon->hit_ob(me, victim, damage_bonus);
                			if( stringp(foo) ) result += foo;
                			else if(intp(foo) ) damage_bonus += foo;
            			}
            			else
            			{
            				foo = me->hit_ob(me, victim, damage_bonus);
                			if( stringp(foo) ) result += foo;
                			else if(intp(foo) ) damage_bonus += foo * 3 / 4;
            			}

            			if( damage_bonus > 0 )
                			damage += (damage_bonus + random(damage_bonus))/2;
            			if( damage < 0 ) damage = 0;

            			// Let combat exp take effect
            			defense_factor = your["combat_exp"];
            			while( random(defense_factor) > my["combat_exp"] )
            			{
            				damage -= damage / 3;
                			defense_factor /= 2;
            			}


            			//(6) Inflict the damage.
            		        damage = victim->receive_damage("kee", damage, me );

            			if( (me->is_killing(victim) || weapon)
            			    && random(damage) > (int)victim->query_temp("apply/armor") )
            			{
            				// We are sure that damage is greater than victim's armor here.
                			victim->receive_wound("kee",damage - (int)victim->query_temp("apply/armor"), me);
                			wounded = 1;
            			}

                        	//if (me->query_temp("ldlh")) result = "\n" + action["action"] + "！\n";
            			result += damage_msg(damage, action["damage_type"]);


            			//(7) Give experience
            		        if( !userp(me) || !userp(victim) )
            		        {
            		        	if( (ap < dp) && (random(my["sen"]*100/my["max_sen"] + me->query_int()*me->query_cps()) > 150) )
            		        	{
            		        		my["combat_exp"] += 1 + random(me->query_int() / 10);
                    				// if( my["potential"] - my["learned_points"] < 100 )
                        				my["potential"] += 1 + random(me->query_int() / 50);
                    				me->improve_skill(attack_skill, 1 + random(me->query_int()));
                			}
                			if( random(your["max_kee"] + your["kee"]) < damage )
                			{
                				your["combat_exp"] += 1 + random(victim->query_int() / 10);
                    				// if( your["potential"] - your["learned_points"] < 100 )
                        				your["potential"] += 1 + random(victim->query_int() / 50);
                			}
            			}
        		}
    		}
    	}

    	result = replace_string( result, "$l", limb );
    	if( objectp(weapon) )
       		result = replace_string( result, "$w", weapon->name() );
    	else if( stringp(action["weapon"]) )
             	result = replace_string( result, "$w", action["weapon"] );
    	if( objectp(victim->query_temp("weapon")) )
        	result = replace_string( result, "$W",victim->query_temp("weapon")->name() );

    	if ( (damage != RESULT_DODGE) && (damage != RESULT_PARRY) )
	{
		message_vision(result, me, victim );
		if ( damage == RESULT_FORCE && me->query("eff_kee")<0 )
		{
			CHANNEL_D->do_channel(victim, "rumor",me->name()+"中了"+victim->name()+"的拨转招式之法，自己把自己打死了。");
	                victim->delete_temp("last_channel_msg");
	                // emotion: comment out to avoid bug //  me->die();
	         }
	}
	else
	{
		if ( ((string)me->query("env/brief_message") != "YES"
		     && (string)victim->query("env/brief_message") != "YES")
		     || me->query_temp("ldlh") )
			message_vision(result, me, victim );
                if( martial_skill = me->query_skill_mapped(attack_skill) )
		{
			fail_hit_msg=SKILL_D(martial_skill)->fail_hit(me, victim);
		 if (stringp(fail_hit_msg)) message_vision(fail_hit_msg,me,victim);
		}
	}

           // condition added to avoid null point exception
        if( me && objectp(me) && wizardp(me) && (string)me->query("env/combat")=="verbose" )
        {
			string debug_msg;
			debug_msg = GRN "AP：" + (ap/100) + "，DP：" + (dp/100) + "，PP：" + (pp/100)
			            + "，Mod：" + (mod_val/100);
        	if( damage > 0 )
                	tell_object(me, debug_msg + "，伤害力：" + damage + NOR + "\n");
        	else
                	tell_object(me, debug_msg + NOR + "\n");
        }

           // condition added to avoid null point exception
        if( victim && objectp(victim) && wizardp(victim) && (string)victim->query("env/combat")=="verbose" )
        {
			string debug_msg;
			debug_msg = GRN "AP：" + (ap/100) + "，DP：" + (dp/100) + "，PP：" + (pp/100)
			            + "，Mod：" + (mod_val/100);
        	if( damage > 0 )
                	tell_object(victim, debug_msg + "，伤害力：" + damage + NOR + "\n");
        	else
            		tell_object(victim, debug_msg + NOR + "\n");
         }

         if( damage > 0 )
         {
         	report_status(victim, wounded);
                if( martial_skill = me->query_skill_mapped(attack_skill) )
                {
                	hit_ob_msg=SKILL_D(martial_skill)->hit_ob_msg(me, victim);
                        if (stringp(hit_ob_msg)) message_vision(hit_ob_msg,me,victim);
        	}

    		if ( me->query_temp("zxzx") == 1 )
         	{
         		"/daemon/class/yaomo/wudidong/qixiu-jian/zxzx"->zxzx_effect(me,victim);
         	}

                if( victim->is_busy() ) victim->interrupt_me(me);
                if( (!me->is_killing(your["id"])) && (!victim->is_killing(my["id"])) )
                {
                	// fight until one side's kee is < 50%
                        if( victim->query("kee") < victim->query("max_kee") * 50 / 100)
                        {
                        	me->remove_enemy(victim);
             			victim->remove_enemy(me);
             			message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);
          		}
        	}
    	 }
    	 else if( me->query_temp("pfmxue") == 1 )
    	      {
    	    		"/daemon/class/kunlun/huntian-jian/xue"->pfmxue_effect(me,victim);
    	      }

        if( functionp(action["post_action"]) )
        	evaluate( action["post_action"], me, victim, weapon, damage);

        if( damage > 0 && attack_type != TYPE_QUICK && me->query_temp("perf_quick") && me->is_fighting(victim) )
        {
        	if( me->query_temp("weapon") && me->query_temp("perf_quick/"+me->query_temp("weapon")->query("skill_type")) )
        	{
        		if( me->query_temp("perf_quick/msg") )
               			message_vision(CYN + me->query_temp("perf_quick/msg") +NOR, me, victim);
                	else
                        	message_vision(CYN + "$N得势不饶人，对$n展开连续攻击。"+NOR, me, victim);
           		do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
           		return 1;
        	}
    	}

        // See if the victim can make a riposte.
    	if( attack_type==TYPE_REGULAR &&  damage < 1 &&  victim->query_temp("guarding") )
    	{
    		victim->set_temp("guarding", 0);
	        if( random(my["cps"]) < 5 )
	        {
	        	message_vision("$N一击不中，露出了破绽！\n", me);
	            	do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
	        }
	        else
	        {
	        	message_vision("$N见$n攻击失误，趁机发动攻击！\n", victim, me);
	            	do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
	        }
    	}

       return damage;
}

// added by emotion
int calculate_wuxing_damage(object me, object victim, int wuxing_damage, int wuxing_type, int op_rate) {
	int wuxing_defense,damage;
	switch(wuxing_type)
	{
		case 0:
			wuxing_defense = victim->query_temp("apply/gold_defense");
			break;
		case 1:
			wuxing_defense = victim->query_temp("apply/water_defense");
			break;
		case 2:
			wuxing_defense = victim->query_temp("apply/wood_defense");
			break;
		case 3:
			wuxing_defense = victim->query_temp("apply/fire_defense");
			break;
		case 4:
			wuxing_defense = victim->query_temp("apply/earth_defense");
			break;
		case 5:
			wuxing_defense = 0;
			break;
	}
	if( wuxing_defense < 0 )
		wuxing_defense = 0;
	if ( random(wuxing_damage)*3 > random(wuxing_defense)*2 ) {
		damage = wuxing_damage - random(wuxing_defense)/2;
		if( damage < 0 )
			damage = 1;
		return damage;
	}
	else if ( op_rate < random(120) )
		return -1;
	else
		return 0;
}
// end -- emotion

//  fight()
//
//  This is called in the attack() defined in F_ATTACK, which handles fighting
//  in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
    object ob, weapon;
    object* my_inv;
    int i, size, temp_value, wuxing_flag, wuxing_type, wuxing_damage,level,all_damage,op_rate;
    string msg, msg_head;

	msg = "";
    if( !living(me) ) return;
    if( me->query_temp("netdead") && !me->query_temp("pkmeet/begin") )  return;
    if( victim->query_temp("netdead") && !victim->query_temp("pkmeet/begin"))   {
        if( member_array( me, victim->query_netdead_enemy() ) == -1 )
        return;     // can't start fight if the victim is already netdead
    }
	//change by kugu
	weapon = me->query_temp("weapon");
	if( weapon && weapon->is_newitem() && userp(me) )
	{
		temp_value = weapon->query("op_exp");
		weapon->set_item_attr("op_exp", temp_value + 1, me );
		level = weapon->query("level");
		op_rate = weapon->op_exp_rate();
	}
	if( !userp(me) && me->query_temp("apply/level") )
		level = me->query_temp("apply/level");
	if( weapon )
		msg_head = "只见$N手中" + weapon->query("name");
	else
	{
		msg_head = "只见$N挥舞着双手施展出";
		op_rate = me->query_temp("apply/op_rate");
	}
	if( !op_rate ) op_rate = 10;
	if( op_rate > 100 ) op_rate = 100;
	//wuxing_type=0;
	//wuxing_damage=me->query_temp("apply/gold_attack");
	for(i=0;i<sizeof(wuxing);i++)
	{
		if( me->query_temp("apply/"+wuxing[i][0]) > 0 )
		{
			wuxing_flag = wuxing_flag + 1;
			all_damage = all_damage + me->query_temp("apply/"+wuxing[i][0]);
		}
		/*if( random(me->query_temp("apply/"+wuxing[i][0]))*3 > random(wuxing_damage)*2+1 )
		{
			wuxing_damage = me->query_temp("apply/"+wuxing[i][0]);
			wuxing_type = wuxing[i][1];
		}*/
	}
	if( wuxing_flag == 5 && random(100) == 5 )
	{
		wuxing_damage = all_damage;
		wuxing_type = 5;
	}
	else
	{
		all_damage = random(all_damage);
		if( all_damage < me->query_temp("apply/"+wuxing[0][0]) && me->query_temp("apply/"+wuxing[0][0]) > 0 )
		{
			wuxing_damage = me->query_temp("apply/"+wuxing[0][0]);
			wuxing_type = wuxing[0][1];
		}
		else if( all_damage < me->query_temp("apply/"+wuxing[0][0])+me->query_temp("apply/"+wuxing[1][0]) && me->query_temp("apply/"+wuxing[1][0]) > 0 )
		{
			wuxing_damage = me->query_temp("apply/"+wuxing[1][0]);
			wuxing_type = wuxing[1][1];
		}
		else if( all_damage < me->query_temp("apply/"+wuxing[0][0])+me->query_temp("apply/"+wuxing[1][0])+me->query_temp("apply/"+wuxing[2][0]) && me->query_temp("apply/"+wuxing[2][0]) > 0 )
		{
			wuxing_damage = me->query_temp("apply/"+wuxing[2][0]);
			wuxing_type = wuxing[2][1];
		}
		else if( all_damage < me->query_temp("apply/"+wuxing[0][0])+me->query_temp("apply/"+wuxing[1][0])+me->query_temp("apply/"+wuxing[2][0])+me->query_temp("apply/"+wuxing[3][0]) && me->query_temp("apply/"+wuxing[3][0]) > 0 )
		{
			wuxing_damage = me->query_temp("apply/"+wuxing[3][0]);
			wuxing_type = wuxing[3][1];
		}
		else
		{
			wuxing_damage = me->query_temp("apply/"+wuxing[4][0]);
			wuxing_type = wuxing[4][1];
		}
	}
	if( wuxing_flag > 0 && random(2) )
	{
		my_inv = all_inventory(victim);
		my_inv = filter(my_inv, (: ($1->query("equipped") == "worn") && ($1->is_newitem()) :) );
		if (sizeof(my_inv) == 0)
			my_inv = 0;
		switch(wuxing_type)
		{
			case 0:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIY + msg_head+HIY"使出";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIY"『金光术』一道金光闪过，在$n身上留下一个窟窿！\n"+ NOR;
							break;
						case 1:
							msg += HIY"『羽箭术』，一支金色长箭从$n身上贯穿而过！\n"+ NOR;
							break;
						case 2:
							msg += HIY"『羽刃术』，一把金色长刀在$n身上留下了深可见骨的伤口！\n"+ NOR;
							break;
						case 3:
							msg += HIY"『羽翼术』，金色的羽翼将$n划得遍体鳞伤！\n"+ NOR;
							break;
						case 4:
							msg += HIY"『神鹰翼扬』，神鹰从天而降，将$n啄得遍体鳞伤！\n"+ NOR;
							break;
						case 5:
							msg += HIY"『金元素风暴』，狂暴的金元素将$n高高抛起，然后$n重重的砸在地上！\n"+ NOR;
							break;
						case 6:
							msg += HIY"『圣光术』，金色的圣光在$n身上造成了巨大的伤害！\n"+ NOR;
							break;
						case 7:
							msg += HIY"『光耀天地』，在无尽的圣光照耀下，$n再没有丝毫反抗的力量！\n"+ NOR;
							break;
						case 8:
							msg += HIY"『天神之怒』，神的力量使$N背后生出六只金色的羽翼，$n跪倒在地，只知道不停的膜拜！\n"+ NOR;
							break;
					}
					if( weapon && weapon->is_newitem() && userp(me) )
					{
						temp_value = weapon->query("fight_exp");
						weapon->set_item_attr("fight_exp", temp_value + 1, me );
					}
					if (wizardp(me))
					{
						tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
					}
					victim->receive_damage("kee", wuxing_damage, me);
					victim->receive_wound("kee", wuxing_damage/2, me);
					message_vision(msg, me, victim);
					report_status(victim);
				}
				else if(wuxing_damage == 0)
				{
					msg += HIY"金系法术, 谁知$n的装备自动生成一层防护，轻松挡住了$N的攻击！\n"NOR;
					message_vision(msg, me, victim);
					if( arrayp(my_inv) )
					ob = my_inv[random(sizeof(my_inv))];
					if( ob )
					{
						temp_value = ob->query("fight_exp");
						ob->set_item_attr("fight_exp", temp_value + 1, victim );
					}
				}
				else
				{
					msg += HIY"金系法术, 谁知$N的控制实在差劲，竟然打歪了！\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 1:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIB + msg_head+HIB"使出";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIB"『漩涡术』，在$n脚下出现一个漩涡，不断的吸收$n的力量！\n"+ NOR;
							break;
						case 1:
							msg += HIB"『涌泉术』，奔流不息的泉水掠夺着$n的力量！\n"+ NOR;
							break;
						case 2:
							msg += HIB"『寒露术』，水滴慢慢凝结在$n的周围，$n不知不觉中行动变得缓慢了！\n"+ NOR;
							break;
						case 3:
							msg += HIB"『凌杀术』，无数冰寒的水滴冻结了$n的身体，封印了$n的力量！\n"+ NOR;
							break;
						case 4:
							msg += HIB"『水蚀术』，来自冥界的腐蚀之水，侵蚀了$n的身体，吞噬了$n的力量！\n"+ NOR;
							break;
						case 5:
							msg += HIB"『水元素风暴』，狂暴的水元素将$n冲的东倒西歪！\n"+ NOR;
							break;
						case 6:
							msg += HIB"『水龙波』，一条晶莹的水龙腾空而起，吐出一道水箭将$n击倒在地！\n"+NOR;
							break;
						case 7:
							msg += HIB"『玄冰水龙』，一条完美的冰龙腾空而起，$n被冰龙那完美的曲线，耀眼的光芒迷住了！\n"+ NOR;
							break;
						case 8:
							msg += HIB"『女神之泪』，司管生命的女神流下怜悯的泪水，$n跪倒在地，要将生命奉献！\n"+ NOR;
							break;
					}
					if( weapon && weapon->is_newitem() && userp(me) )
					{
						temp_value = weapon->query("fight_exp");
						weapon->set_item_attr("fight_exp", temp_value + 1, me );
					}
					if (wizardp(me))
					{
						tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
					}
					victim->receive_damage("kee", wuxing_damage/3, me);
					victim->receive_wound("kee", wuxing_damage/5, me);
					temp_value = victim->query("force");
					if ( temp_value > wuxing_damage )
						temp_value = wuxing_damage*2/3;
					victim->add("force", -temp_value);
					me->add("force", temp_value);
					temp_value = me->query("max_force")*2;
					if (me->query("force") > temp_value)
					me->set("force", temp_value);
					message_vision(msg, me, victim);
					report_status(victim);
				}
				else if(wuxing_damage == 0)
				{
					msg += HIB"水系法术, 谁知$n的装备自动生成一层防护，轻松挡住了$N的攻击！\n"NOR;
					message_vision(msg, me, victim);
					if( arrayp(my_inv) )
					ob = my_inv[random(sizeof(my_inv))];
					if( ob )
					{
						temp_value = ob->query("fight_exp");
						ob->set_item_attr("fight_exp", temp_value + 1, victim );
					}
				}
				else
				{
					msg += HIB"水系法术, 谁知$N的控制实在差劲，竟然打歪了！\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 2:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIG + msg_head+HIG"使出";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIG"『驱藤术』，一根树藤从$n脚下钻出，$n被刺了一下，觉得有些不对劲！\n"+ NOR;
							break;
						case 1:
							msg += HIG"『鬼藤术』，漆黑的树藤，散发出黑色的气息，$n吸入一些，精神有些委靡不振了！\n"+ NOR;
							break;
						case 2:
							msg += HIG"『荆棘术』，一束荆棘从$n脚下钻出，$n被刺了一下，觉得有些不对劲！\n"+ NOR;
							break;
						case 3:
							msg += HIG"『荆棘阵』，无数的荆棘从地下钻出，将$n绊住，$n显得心烦气躁了！\n"+ NOR;
							break;
						case 4:
							msg += HIG"『落木术』，一根无比巨大的木头重重砸在$n头上，$n立时神智不清了！\n"+ NOR;
							break;
						case 5:
							msg += HIG"『木元素风暴』，狂暴的木元素吹得$n分不出东南西北了！\n"+ NOR;
							break;
						case 6:
							msg += HIG"『长生诀』，$n四周的植物开始疯狂的生长，将$n弄得眼花缭乱！\n"+NOR;
							break;
						case 7:
							msg += HIG"『精灵之心』，秉承大自然至纯之美的精灵，用她那纯净的心灵将$n深深感化！\n"+ NOR;
							break;
						case 8:
							msg += HIG"『生长的旋律』，埋藏于地下的种子，在生命的乐章中发芽成长，数不清的植物从地下钻出，$n被完全惊呆了！\n"+ NOR;
							break;
					}
					if( weapon && weapon->is_newitem() && userp(me) )
					{
						temp_value = weapon->query("fight_exp");
						weapon->set_item_attr("fight_exp", temp_value + 1, me );
					}
					if (wizardp(me))
					{
						tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
					}
					victim->receive_damage("sen", wuxing_damage, me);
					victim->receive_wound("sen", wuxing_damage/2, me);
					message_vision(msg, me, victim);
					report_sen_status(victim);
				}
				else if(wuxing_damage == 0)
				{
					msg += HIG"木系法术, 谁知$n的装备自动生成一层防护，轻松挡住了$N的攻击！\n"NOR;
					message_vision(msg, me, victim);
					if( arrayp(my_inv) )
					ob = my_inv[random(sizeof(my_inv))];
					if( ob )
					{
						temp_value = ob->query("fight_exp");
						ob->set_item_attr("fight_exp", temp_value + 1, victim );
					}
				}
				else
				{
					msg += HIG"木系法术, 谁知$N的控制实在差劲，竟然打歪了！\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 3:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIR + msg_head+HIR"使出";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIR"『幻火术』，$n一不小心被一道火舌舔中，登时有些头重脚轻！\n"+ NOR;
							break;
						case 1:
							msg += HIR"『火球术』，一个炽热的火球飞向$n，在$n身上留下一个焦黑的窟窿！\n"+ NOR;
							break;
						case 2:
							msg += HIR"『烈焰术』，炽热的火焰燃烧起来，$n都快被烤糊了！\n"+ NOR;
							break;
						case 3:
							msg += HIR"『爆炎术』，被压缩的火球在$n身边爆炸，$n被炸的血肉模糊！\n"+ NOR;
							break;
						case 4:
							msg += HIR"『黑炎术』，来自地狱的火焰燃烧起来，$n被烤得迷糊了！\n"+ NOR;
							break;
						case 5:
							msg += HIR"『火元素风暴』，狂暴的火元素将$n烧了个焦黑！\n"+ NOR;
							break;
						case 6:
							msg += HIR"『火龙狂舞』，一条火焰组成的飞龙向着$n飞去，$n被吓坏了！\n"+NOR;
							break;
						case 7:
							msg += HIR"『三味真火』，天地间至纯的火焰，燃烧了$n的肢体，燃烧了$n的法力！\n"+ NOR;
							break;
						case 8:
							msg += HIR"『火神之舞』，火焰的神灵，激情的火焰之舞，完全震慑了$n的灵魂！\n"+ NOR;
							break;
					}
					if( weapon && weapon->is_newitem() && userp(me) )
					{
						temp_value = weapon->query("fight_exp");
						weapon->set_item_attr("fight_exp", temp_value + 1, me );
					}
					if (wizardp(me))
					{
						tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
					}
					victim->receive_damage("kee", wuxing_damage/2, me);
					victim->receive_wound("kee", wuxing_damage/5, me);
					temp_value = victim->query("mana");
					if ( temp_value > wuxing_damage )
						temp_value = wuxing_damage/2;
					victim->add("mana", -temp_value);
					me->add("mana", temp_value);
					temp_value = me->query("max_mana")*2;
					if (me->query("mana") > temp_value)
					me->set("mana", temp_value);
					message_vision(msg, me, victim);
					report_status(victim);
				}
				else if(wuxing_damage == 0)
				{
					msg += HIR"火系法术, 谁知$n的装备自动生成一层防护，轻松挡住了$N的攻击！\n"NOR;
					message_vision(msg, me, victim);
					if( arrayp(my_inv) )
					ob = my_inv[random(sizeof(my_inv))];
					if( ob )
					{
						temp_value = ob->query("fight_exp");
						ob->set_item_attr("fight_exp", temp_value + 1, victim );
					}
				}
				else
				{
					msg += HIR"火系法术, 谁知$N的控制实在差劲，竟然打歪了！\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 4:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = YELGRN + msg_head+YELGRN"使出";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += YELGRN"『地裂术』，$n一不小心掉进了一个巨大的裂缝里！\n"+ NOR;
							break;
						case 1:
							msg += YELGRN"『流沙术』，流沙出现在$n脚下，$n越是挣扎陷得就越深！\n"+ NOR;
							break;
						case 2:
							msg += YELGRN"『地灵缚』，$n脚下的土地变成了一副枷锁，将$n牢牢定住！\n"+ NOR;
							break;
						case 3:
							msg += YELGRN"『落石术』，空中突然落下巨石，将$n砸入泥土之中！\n"+ NOR;
							break;
						case 4:
							msg += YELGRN"『地龙震』，地下的巨龙苏醒了，将$n牢牢的禁锢了！\n"+ NOR;
							break;
						case 5:
							msg += YELGRN"『土元素风暴』，狂暴的土元素将$n震的七晕八素！\n"+ NOR;
							break;
						case 6:
							msg += YELGRN"『天地鸣动』，大地开始震动，吓得$n不敢动弹！\n"+NOR;
							break;
						case 7:
							msg += YELGRN"『地牢结界』，大地的力量凝聚成一个原形的结界，将$n囚禁在内！\n"+ NOR;
							break;
						case 8:
							msg += YELGRN"『大地之惠』，大地之神，众生之母，仁慈的光芒下，$n怀着感恩的心，顶礼膜拜！\n"+ NOR;
							break;
					}
					if( weapon && weapon->is_newitem() && userp(me) )
					{
						temp_value = weapon->query("fight_exp");
						weapon->set_item_attr("fight_exp", temp_value + 1, me );
					}
					if (wizardp(me))
					{
						tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
					}
					victim->receive_damage("sen", wuxing_damage/3, me);
					victim->receive_wound("sen", wuxing_damage/6, me);
					victim->start_busy(random(2));
					message_vision(msg, me, victim);
					report_sen_status(victim);
				}
				else if(wuxing_damage == 0)
				{
					msg += YELGRN"土系法术, 谁知$n的装备自动生成一层防护，轻松挡住了$N的攻击！\n"NOR;
					message_vision(msg, me, victim);
					if( arrayp(my_inv) )
					ob = my_inv[random(sizeof(my_inv))];
					if( ob )
					{
						temp_value = ob->query("fight_exp");
						ob->set_item_attr("fight_exp", temp_value + 1, victim );
					}
				}
				else
				{
					msg += YELGRN"土系法术, 谁知$N的控制实在差劲，竟然打歪了！\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 5:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIM + msg_head+HIM"使出";;
				if(wuxing_damage>0)
				{
					if( random(level) < 5 )
						msg += HIM"『五行元素风暴』，狂暴的元素禁锢$n了身体，并对$n造成了极大的伤害！\n"+ NOR;
					else
						msg += HIM"『众神之怒』， 狂暴的力量几乎将$n撕成碎片！\n"NOR;
					if( weapon && weapon->is_newitem() && userp(me) )
					{
						temp_value = weapon->query("fight_exp");
						weapon->set_item_attr("fight_exp", temp_value + 1, me );
					}
					if (wizardp(me))
					{
						tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
					}
					victim->receive_damage("sen", wuxing_damage, me);
					victim->receive_wound("sen", wuxing_damage/2, me);
					victim->receive_damage("kee", wuxing_damage, me);
					victim->receive_wound("kee", wuxing_damage/2, me);
					victim->start_busy(1+random(2));
					message_vision(msg, me, victim);
					report_status(victim);
					report_sen_status(victim);
				}
				else if(wuxing_damage == 0)
				{
					msg += HIM"五行法术, 谁知$n的装备自动生成一层防护，轻松挡住了$N的攻击！\n"NOR;
					message_vision(msg, me, victim);
					if( arrayp(my_inv) )
					ob = my_inv[random(sizeof(my_inv))];
					if( ob )
					{
						temp_value = ob->query("fight_exp");
						ob->set_item_attr("fight_exp", temp_value + 1, victim );
					}
				}
				else
				{
					msg += HIM"五行法术, 谁知$N的控制实在差劲，竟然打歪了！\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
		}
	}

	//end
    // added by emotion
    /*wuxing_flag = 1;
	if (userp(me)) {
		my_inv = all_inventory(me);
		size = sizeof(my_inv);
		for (i = 0; i < size; i++) {
			object item;
			item = my_inv[i];
			if (item->is_newitem() && (item->is_armor() || item->is_weapon()) && item->query("equipped")) {
				temp_value = item->query("fight_exp");
				item->set_item_attr("fight_exp", temp_value + 1, me );
				temp_value = item->query("op_exp");
				item->set_item_attr("op_exp", temp_value + 1, me );
			}
		}
		weapon = me->query_temp("weapon");
		if (!objectp(weapon) || !weapon->is_newitem())
			wuxing_flag = 0;
		else if (random(100) > weapon->op_exp_rate())
			wuxing_flag = 0;
	}
	if (wuxing_flag) {
		if (userp(me))
			msg_head = "只见$N手中的" + weapon->query("name");
		else {
			msg_head = "只见$N的";
			switch(random(5)) {
				case 0:
				default:
					msg_head += "双眼";
					break;
				case 1:
					msg_head += "手心";
					break;
				case 2:
					msg_head += "脚底";
					break;
				case 3:
					msg_head += "后背";
					break;
				case 4:
					msg_head += "丹田";
					break;
			}
		}
		switch(me->query_temp("newitem_wuxing_counter")) {
			case 0:
			default:
					wuxing_damage = calculate_wuxing_damage(me, victim, "gold");
					if (wuxing_damage>0) {
						msg = HIY + msg_head + HIY + "向$n射出无数利剑, $n无从躲闪, 被扎得遍体鳞伤!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						victim->receive_damage("kee", wuxing_damage, me);
						victim->receive_wound("kee", wuxing_damage/2, me);
						message_vision(msg, me, victim);
						report_status(victim);
					} else  if (wuxing_damage == 0){
						msg = msg_head + "向$n射出无数利剑, 却被$n谈笑间在利剑的间隙中游走, 轻松避开!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 1:
					wuxing_damage = calculate_wuxing_damage(me, victim, "wood");
					if (wuxing_damage>0) {
						msg = HIG + msg_head + HIG + "偷偷飞出一根无比巨大的神木, $n一个没留神, 被重重地砸在了头上, 立时神智不清!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						victim->receive_damage("sen", wuxing_damage, me);
						victim->receive_wound("sen", wuxing_damage/2, me);
						message_vision(msg, me, victim);
						report_sen_status(victim);
					} else if (wuxing_damage == 0){
						msg = msg_head + "偷偷飞出一根无比巨大的神木, 早被$n看见, 略一斜身, 神木重重地砸在了地上!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 2:
					wuxing_damage = calculate_wuxing_damage(me, victim, "water");
					if (wuxing_damage > 0) {
						msg = HIB + msg_head + HIB + "幻出一条晶莹的水龙向$n飞去, 硬生生从$n体内吸出了几股内力并传回给$N!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						temp_value = victim->query("force");
						if ( temp_value > 0 ) {
							if ( temp_value > wuxing_damage ) {
								victim->add("force", -wuxing_damage);
								me->add("force", wuxing_damage);
							} else {
								victim->add("force", -temp_value);
								me->add("force", temp_value);
							}
							temp_value = me->query("max_force")*2;
							if (me->query("force") > temp_value)
								me->set("force", temp_value);
						}
						message_vision(msg, me, victim);
					} else  if (wuxing_damage == 0){
						msg = msg_head + "幻出一条晶莹的水龙向$n飞去, 不料$n哈哈一笑, 用手一挥, 水龙立刻散落在地不成形状!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 3:
					wuxing_damage = calculate_wuxing_damage(me, victim, "fire");
					if (wuxing_damage>0) {
						msg = HIR + msg_head + HIR + "幻出一群火鸟向$n啄去. $n虽然左右扑打, 还是被火鸟衔去几粒内丹. $N接过火鸟抢来的内丹, 一口吞了下去!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						temp_value = victim->query("mana");
						if ( temp_value > 0 ) {
							if ( temp_value > wuxing_damage ) {
								victim->add("mana", -wuxing_damage);
								me->add("mana", wuxing_damage);
							} else {
								victim->add("mana", -temp_value);
								me->add("mana", temp_value);
							}
							temp_value = me->query("max_mana")*2;
							if (me->query("mana") > temp_value)
								me->set("mana", temp_value);
						}
						message_vision(msg, me, victim);
					} else  if (wuxing_damage == 0){
						msg = msg_head + "幻出一群火鸟向$n啄去. 确见$n口中念念有辞, 天空立即下起一阵豪雨, 把那些火鸟只冲得干干净净!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 4:
					wuxing_damage = calculate_wuxing_damage(me, victim, "earth");
					if (wuxing_damage>0) {
						msg = YELGRN + msg_head + YELGRN + "暴起满天尘土向$n卷去, $n一时没有防备, 被迷了口眼手忙脚乱!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						if ( !victim->is_busy() )
							victim->start_busy( 1 + random( 2 ) );
						message_vision(msg, me, victim);
					} else  if (wuxing_damage == 0){
						msg = msg_head + "暴起满天尘土向$n卷去, $n却挥动衣袖, 扯起一阵大风, 早把尘土刮到西天灵山去了!\n";
						message_vision(msg, me, victim);
					}
				break;
		}
		me->add_temp("newitem_wuxing_counter", 1);
		if ( me->query_temp("newitem_wuxing_counter") > 4 )
			me->set_temp("newitem_wuxing_counter", 0);
	}*/
    // end add -- emotion

    if( !me->visible(victim)
    && (random(100 + (int)me->query_skill("perception")) < 100) )
        return;

    // If victim is busy or unconcious, always take the chance to make an attack.
    // added: if victim is in "no_move", similar to "is_busy".
    if( victim->is_busy() || (victim->query_temp("no_move")) || !living(victim) ) {
        me->set_temp("guarding", 0);
        if( !victim->is_fighting(me) ) victim->fight_ob(me);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);

    // Else, see if we are brave enough to make an aggressive action.
    } else if( random( (int)victim->query_cps() * 3 ) < ((int)me->query_cor() + (int)me->query("bellicosity") / 50) ) {
        me->set_temp("guarding", 0);
        if( !victim->is_fighting(me) ) victim->fight_ob(me);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);

    // Else, we just start guarding.
    } else if( !me->query_temp("guarding") ) {
        me->set_temp("guarding", 1);
        message_vision( guard_msg[random(sizeof(guard_msg))], me, victim);
        return;
    } else return;
}

//  auto_fight()
//
//  This function is to start an automatically fight. Currently this is
//  used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
    // Don't let NPC autofight NPC.
    if( !userp(me) && !userp(obj) ) return;

    // Because most of the cases that we cannot start a fight cannot be checked
    // before we really call the kill_ob(), so we just make sure we have no
    // aggressive callout wating here.
    if( me->query_temp("looking_for_trouble") ) return;
    me->set_temp("looking_for_trouble", 1);

    // This call_out gives victim a chance to slip trough the fierce guys.
    call_out( "start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
    int bellicosity;

    if( !me ) return;// Are we still exist( not becoming a corpse )?
    me->set_temp("looking_for_trouble", 0);
    if( !obj ) return;

    if( wizardp(obj) ) return;

    if( me->is_fighting(obj)                // Are we busy fighting?
    ||  !living(me)                         // Are we capable for a fight?
    ||  environment(me)!=environment(obj)   // Are we still in the same room?
    ||  environment(me)->query("no_fight")  // Are we in a peace room?
    )   return;

    bellicosity = (int)me->query("bellicosity");
    message_vision("$N用一种异样的眼神扫视着在场的每一个人。\n", me);

    if( (int)me->query("force") > (random(bellicosity) + bellicosity)/2 ) return;

    if( bellicosity > (int)me->query("score")
    &&  !wizardp(obj) ) {

        // auto kill, mark my_killer_list. -- mon 9/23/98
//      if(userp(me) && userp(obj)) {
//      set_my_killer_list(me, obj);
//      }

        message_vision("$N对着$n喝道：" + RANK_D->query_self_rude(me)
        + "看你实在很不顺眼，去死吧。\n", me, obj);
me->set_temp("kill/target/"+obj->query("id"),1);
        me->kill_ob(obj);
    } else {
        message_vision("$N对着$n喝道：喂！" + RANK_D->query_rude(obj)
            + "，" + RANK_D->query_self_rude(me) + "正想找人打架，陪我玩两手吧！\n",
            me, obj);
        me->fight_ob(obj);
    }
}

void start_hatred(object me, object obj)
{
    if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?

    me->set_temp("looking_for_trouble", 0);

    if( me->is_fighting(obj)                // Are we busy fighting?
    ||  !living(me)                         // Are we capable for a fight?
    ||  environment(me)!=environment(obj)   // Are we still in the same room?
    ||  environment(me)->query("no_fight")  // Are we in a peace room?
    )   return;

    // We found our hatred! Charge!
    message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
    me->kill_ob(obj);
}

void start_vendetta(object me, object obj)
{
    if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?

    me->set_temp("looking_for_trouble", 0);

    if( me->is_fighting(obj)                // Are we busy fighting?
    ||  !living(me)                         // Are we capable for a fight?
    ||  environment(me)!=environment(obj)   // Are we still in the same room?
    ||  environment(me)->query("no_fight")  // Are we in a peace room?
    )   return;

    // We found our vendetta opponent! Charge!
    me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
    if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?

    me->set_temp("looking_for_trouble", 0);

    if( me->is_fighting(obj)                // Are we busy fighting?
    ||  !living(me)                         // Are we capable for a fight?
    ||  environment(me)!=environment(obj)   // Are we still in the same room?
    ||  environment(me)->query("no_fight")  // Are we in a peace room?
    )   return;

    // We got a nice victim! Kill him/her/it!!!
    me->kill_ob(obj);
}

//add by yesi
void start_pkmeet(object me, object obj)
{
	if( !me || !obj ) return;
	me->set_temp("looking_for_trouble", 0);

    if( me->is_fighting(obj)                // Are we busy fighting?
    ||  !living(me)                         // Are we capable for a fight?
    ||  environment(me)!=environment(obj)   // Are we still in the same room?
    ||  environment(me)->query("no_pkmeet")  // Are we in a peace room?
    )   return;

    me->kill_ob(obj);

}


// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event, string msg)
{
 if (ob->query_temp("pkgame")) return;
        switch(event) {
                case "dead":
                        message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n", ob);
                        break;
         case "unconcious":
                        message_vision("\n$N神志迷糊，脚下一个不稳，倒在地上昏了过去。\n\n", ob);
                        break;
                case "revive":
                         if(ob->query("blind") || ob->query("race") != "人类")
			     message_vision("\n$N身子一颤，扭动了几下，清醒了过来。\n\n", ob);
			else if(ob->query("mute"))
			     message_vision("\n$N慢慢清醒了过来，睁开眼睛站起来摇了摇头。\n\n", ob);
			else message_vision("\n$N身子动了动，口中呻吟了几声，清醒过来。\n\n", ob);
                        break;
                case "death_rumor":
                        CHANNEL_D->do_channel(this_object(),"rumor",msg);
                        break;
        }
}

void winner_reward(object killer, object victim)
{
    killer->defeated_enemy(victim);
}



void killer_reward(object killer, object victim)
{
	int bls,i;
	int iRealDie ; // add by canoe for Start PkGame ?
	string vmark,killmsg,rkmsg;
	int gain,gain1,lose;
	string str,killerid;
	object weapon,*oUser,wiz,*fire; //add by take for CS
 /**************************************************/
    //added by canoe
   string *vics,*kils;
   mapping killvic,vickill;

	if ( killer->is_manmade_npc() || victim->is_manmade_npc() ) {
			JJ_MANMADE_NPCD->announce_msg( "在[" + environment(killer)->query("short") + "] " + killer->query("name")
			      + "(" + killer->query("id") +") 杀死了 " + victim->query("name")
			      + "(" + victim->query("id") + ")");
	}
    killvic=killer->query_temp("kill/target");
    if(mapp(killvic)&&sizeof(killvic))
       vics = keys(killvic);

   vickill=victim->query_temp("kill/target");
   if(mapp(vickill)&&sizeof(vickill))
	   kils = keys(vickill);
/************************************************************/
	// Call the mudlib killer apply.
	killer->killed_enemy(victim);

	if( userp(victim) ) { // victim is user.

	    string *my_killer_list;
	    int init_killer;
	    int no_pk;
	    // edit by canoe for PkGame 02-1-17 12:11
	   iRealDie =  "/cmds/usr/pkgame"->query_pk() ;
	   if ( iRealDie && userp(killer) )
	   {
	   	if ( killer != victim )
	   	{
	   		switch ( random(4) )
	   		{
	   			case 0 : killmsg = "$o光荣牺牲于$t的手下。" ;
	   				 break ;
	   			case 1 : killmsg = "$t神勇无敌，将$o斩于马下。";
	   				 break ;
	   			case 2 : killmsg = "惨叫声中，$t已将$o首级提在手中。";
	   				 break ;
	   			default : killmsg = "一声惨叫，$o已经被$t送去西天。";
	   		}
	   		rkmsg = victim->query("name")+"（"+victim->query("id")+"）" ;
	   		killmsg = replace_string ( killmsg, "$o", rkmsg );
	   		rkmsg = killer->query("name")+"（"+killer->query("id")+"）" ;
	   		killmsg = replace_string ( killmsg, "$t", rkmsg );
	   		if ((killer->query_temp("pkgame"))==(victim->query_temp("pkgame"))) killer->add_temp( "pgwin" , -1 );  // 对cs系统的限制
	   		if ((killer->query_temp("pkgame"))!=(victim->query_temp("pkgame"))) killer->add_temp( "pgwin" , 1 );   // 同上
	   		if (!victim->query_temp("pkgame") && userp(victim)) killer->die(); //同上
	   		CHANNEL_D->do_channel ( this_object() , "rumor" , killmsg );
	   	}else if ( killer == victim )
	   	{
	   		CHANNEL_D->do_channel ( this_object() , "rumor" , "由于ｃｓ大赛过于激烈"HIW+victim->query("name")+HIM"不堪承受强大的对手所带来的压力，身心憔悴死在安全区。" );
	   		if ( killer->query_temp("pkgame") ) killer->add_temp( "pgwin" , -1 );
	   	}
	      	victim->clear_condition();
		victim->delete_temp("last_fainted_from");
		killer->remove_all_killer();
		victim->remove_all_killer();
		if ( killer != victim )
		message_vision(HIR"\n\n眼见$N不敌，被$n一脚踹到CS休息室去了。\n"NOR,victim,killer);
	        else if ( killer == victim )
	        message_vision(HIR"\n\n$N太胆小了，还是先去休息室喘口气再来吧。\n"NOR,victim);
	        if (victim->query_temp("pkgame")) victim->move("/u/take/waitpk");
	        oUser = users();
		for ( i = 0 ; i < sizeof(oUser) ; i ++ )
        	{
        		if ((oUser[i]->query_temp("pkgame")==victim->query_temp("pkgame")) && (environment(oUser[i])->query("short") != HIR"CS休息室"NOR))
        			i = sizeof(oUser)+1;
                }
        	if ( i == sizeof(oUser) )
        	{
        		if ( killer == victim )
        		{
        			if ( (killer->query_temp("pkgame") == "t") && (sizeof(fire) == 0) )
        			{
        				message( "system", BLINK HIR"\n【 CS 大赛】： 本局结束，此局比赛"+HIY"大侠"+BLINK HIR"组获胜,请各位准备5秒钟后开始下一局比赛。。。。。。\n" NOR, users() );
       					"/cmds/usr/pkgame"->over();
       					"/cmds/usr/pkgame"->query_Win("ct");
       				}
        			if ( killer->query_temp("pkgame") == "ct" )
        			{
       					message( "system", BLINK HIR"\n【 CS 大赛】： 本局结束，此局比赛"+HIY"纵火犯"+BLINK HIR"组获胜,请各位准备5秒钟后开始下一局比赛。。。。。。\n" NOR, users() );
       					"/cmds/usr/pkgame"->over();
       					"/cmds/usr/pkgame"->query_Win("t");
       				}
       			}
       			if ( killer != victim )
       			{
       				if ( killer->query_temp("pkgame") == "t")
        			{
       					message( "system", BLINK HIR"\n【 CS 大赛】： 本局结束，此局比赛"+HIY"纵火犯"+BLINK HIR"组获胜,请各位准备5秒钟后开始下一局比赛。。。。。。\n" NOR, users() );
       					"/cmds/usr/pkgame"->over();
       					"/cmds/usr/pkgame"->query_Win("t");
       				}
       				fire = children ("/d/dntg/sky/obj/fire");
       				if ( (killer->query_temp("pkgame") == "ct") && (sizeof(fire) == 0) )
        			{
        				message( "system", BLINK HIR"\n【 CS 大赛】： 本局结束，此局比赛"+HIY"大侠"+BLINK HIR"组获胜,请各位准备5秒钟后开始下一局比赛。。。。。。\n" NOR, users() );
       					"/cmds/usr/pkgame"->over();
       					"/cmds/usr/pkgame"->query_Win("ct");
       				}
       			}
              	 }
         return ; // by take for cs 2002.2.1 17:56
        }
	else
	{
	   // end edit by canoe for PkGame 02-1-17 12:11
	   killer->add("PKS", 1);

	   killerid=killer->query("id");

	   // mon 8/4/98
	   // to see whether the killer has init the kill on me.
	   // if yes, then this is PK. (init_killer!=-1)
	   // if no, (means the victim init the kill and got killed),
	   // then treat this as normal death. (init_killer==-1)
	   my_killer_list=victim->query_temp("my_killer_list");
	   victim->delete_temp("my_killer_list");

	   if(!my_killer_list) init_killer=-1;
	   else init_killer=member_array(killerid, my_killer_list);

	   no_pk=killer->query_condition("no_pk_time");
	   if(no_pk>10) init_killer=1;
	} // killed by a player who
	   // has PK record, then this is PK.
           // regardless who init it.

///////////////////////////////////////////////////////////////////////
killmsg=killer->query_temp("kill_msg");
    if(killmsg)
    {
	switch (killmsg)
	{
		case "slash":
	 	{	rkmsg="斩";	}
		break;
		case "slice":
	 	{	rkmsg="砍";	}
		break;
		case "chop":
	 	{	rkmsg="劈";	}
		break;
		case "hack":
	 	{	rkmsg="劈";	}
		break;
		case "thruse":
	 	{	rkmsg="刺";	}
		break;
		case "pierce":
	 	{	rkmsg="刺";	}
		break;
		case "wave":
	 	{	rkmsg="鞭";	}
		break;
		case "whip":
	 	{	rkmsg="抽";	}
		break;
		case "impale":
	 	{	rkmsg="戳";	}
		break;
		case "rake":
	 	{	rkmsg="筑";	}
		break;
		case "bash":
	 	{	rkmsg="砸";	}
		break;
		case "crush":
	 	{	rkmsg="砸";	}
		break;
		case "slam":
	 	{	rkmsg="挫";	}
		break;
		case "throw":
	 	{	rkmsg="射";	}
		break;
		case "shoot":
	 	{	rkmsg="射";	}
		break;
//now start cast :
//		case "cast_qiankun":	//非攻击性 transfer , chuqiao, qiankun, yinshen
//		{	rkmsg="";	}
//		break;
		case "cast_zhenhuo":
		{	rkmsg="太乙真火";		}
		break;
		case "cast_baxian":
		{	rkmsg="八仙大阵";		}
		break;
		case "cast_bighammer":
		{	rkmsg="大力降魔杵";		}
		break;
		case "cast_jingang":
		{	rkmsg="召唤金刚";		}
		break;
		case "cast_jinguzhou":
		{	rkmsg="紧箍咒";		}
		break;
		case "cast_thunder":
		{	rkmsg="五雷咒";		}
		break;
		case "cast_invocation":
		{	rkmsg="召唤天将";		}
		break;
		case "cast_fenshen":
		{	rkmsg="分身术";		}
		break;
		case "cast_dingshen":
		{	rkmsg="定身法";		}
		break;
		case "cast_light":
		{	rkmsg="苍灵箭";		}
		break;
		case "cast_jieti"://escape, tudun, suliao, huanying
		{	rkmsg="天魔解体大法";		}
		break;
		case "cast_sanmei":
		{	rkmsg="三味真火";		}
		break;
		case "cast_zhuang":
		{	rkmsg="平天大法";		}
		break;
		case "cast_arrow":
		{	rkmsg="落日神箭";		}
		break;
		case "cast_shiyue":// mihun huimeng
		{	rkmsg="蚀月咒";		}
		break;
		case "cast_hufa":
		{	rkmsg="召唤护法";		}
		break;
		case "cast_freez":
		{	rkmsg="雪舞风灵";		}
		break;
		case "cast_jiushen":
		{       rkmsg="酒神";       }
		break;
		case "cast_jianshen":
		{       rkmsg="剑神";       }
		break;
		case "cast_gouhun"://miwu
		{	rkmsg="勾魂术";		}
		break;
		case "cast_animate":
		{	rkmsg="复活鬼魂";		}
		break;
/*		case "cast_":
		{	rkmsg="";		}
		break;
*/
// now start perform msg
		case "perform_sanban":
		{	rkmsg="无敌三板斧";		}
		break;
		case "perform_qiangjian":
		{	rkmsg="枪里加锏";		}
		break;
		case "perform_storm":
		{	rkmsg="暴风骤雨";		}
		break;
		case "perform_diyu":
		{	rkmsg="我入地狱";		}
		break;
		case "perform_pili":
		{	rkmsg="霹雳三打";		}
		break;
		case "perform_qiankun":
		{	rkmsg="乾坤一棒";		}
		break;
		case "perform_pozhan":
		{	rkmsg="破绽百出";		}
		break;
		case "perform_zhangxinlei":
		{	rkmsg="掌心雷";		}
		break;
		case "perform_flower":
		{	rkmsg="天女散花";	}
		break;
		case "perform_diezhang":
		{	rkmsg="叠掌";		}
		break;
		case "perform_huifeng":
		{	rkmsg="风回";		}
		break;
		case "perform_wuxue":
		{	rkmsg="舞雪";		}
		break;
		case "perform_sheshen":
		{	rkmsg="舍身技";		}
		break;
		case "perform_three":
		{	rkmsg="神·人·鬼";	}
		break;
		case "perform_chaofeng":
		{	rkmsg="百鸟朝凤";	}
		break;
/*		case "perform_":
		{	rkmsg="";		}
		break;
*/

//now start exert .........// 非攻击性 recover refresh transfer regenerate heal lifeheal
		case "exert_sheqi":
		{	rkmsg="摄气";		}
		break;
		case "exert_roar":
		{	rkmsg="龙吟";		}
		break;

		case "special_msg"://特殊的攻击
		{	rkmsg=killer->query_temp("special_msg");
			killer->delete_temp("special_msg");
		}
		break;
	}
      }//if(killmsg)




           if(userp(killer) && init_killer!=-1) { // killer is user.
            // killer is user.
	     killer->apply_condition("no_pk_time",240+no_pk);
	       //limit on how many one can pk in a row.
             lose=victim_lose(killer,victim,killerid);
	     gain=lose*2/3;
	     if(gain<0) gain=0;
	     victim->delete_temp("last_fainted_from");

	     if(lose>100)
	       killer->delete("kill/last_killer");
	     //any one can kill this killer to
	     //get maximum dx benefit.
	     //including the one who last killed
	     //this killer.
	     //here check lose>100, so one can't
	     //pk a newbie to erase the last_killer flag.

	     ////modified by aqing for fanren system

	     victim->set("kill/last_killer",killerid);
	     //the victim is protected for repeated
	     //killing by the same killer.
	     victim->set("kill/last_lose",gain);

	     victim_penalty(victim);

//      add by dragon for PK rumor

			weapon=killer->query_temp("kill_weapon");
			if(weapon && rkmsg)
			{
	     		str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"用"HIY+weapon->name()+HIM+rkmsg+"死了。"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			} else {
			if(rkmsg && !weapon)
			{
			str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"用一招"+HIW"“"+rkmsg+"”"+HIM"送去见了阎王。"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			}else if(weapon && !rkmsg){
			str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"用"HIY+weapon->name()+HIM"送去了见了阎王。"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
					   }else {
			str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"杀死了。"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
						  }



	     	}
	     	if(!victim->query("tongji/fanren")&&vics&&member_array(victim->query("id"),vics)>-1)
	{

	  message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer->name(1)+"无视王法，滥伤人命，打死了"+victim->name(1)+"，现正被官府通缉！\n"+NOR,users());
	  killer->set("tongji/fanren",1);
	  killer->set("tongji/mudage",killer->query("mud_age"));
	  //added for prison
	  killer->add("tongji/pktime",1);
	  killer->delete_temp("kill/target/"+victim->query("id"));
	  str = "听说"+killer->name(1)+"杀了人，正在逃命。";
	  CHANNEL_D->do_channel(this_object(), "rumor",str);
	  if(killer->query("tongji/pktime")>=3)
            {
                  killer->move("/d/wiz/dalao");
          message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer->query("name")+"连续杀伤人命，现被关进大牢，待秋后发落！\n"NOR,users());
            }
	}
	else if(victim->query("tongji/fanren"))
	{

	message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer->name(1)+"杀死通缉犯"+victim->name(1)+"有功，现通报嘉奖！\n"+NOR,users());
	killer->add("kill/pkgain",gain);
        killer->add("combat_exp",gain);
        killer->add("PKFANREN",1);
	victim->delete("tongji");
        str=chinese_daoxing(gain);
        if(strlen(str)<=1)
	str="零点";
        str=killer->name(1)+"得到了"+str+"道行！";
        str=victim->name(1)+"被"+killer->name(1)+
            "就地正法。"+str;
        CHANNEL_D->do_channel(this_object(), "rumor",str);

       }else if(kils&&member_array(killer->query("id"),kils)>-1)
       {

        str=victim->name(1)+"被"+killer->name(1)+
            "正当防卫杀死了。";
        CHANNEL_D->do_channel(this_object(), "rumor",str);
       }else {

	message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer->name(1)+"失手打死了"+victim->name(1)+"，现已逃命，望知其下落者，速报知官府！\n"+NOR,users());
	killer->set("tongji/fanren",1);
	killer->set("tongji/mudage",killer->query("mud_age"));
	killer->add("tongji/pktime",1);
	//added for prison
	killer->delete_temp("kill/target/"+victim->query("id"));
	str = "听说"+killer->name(1)+"因过失伤人，正被官府通缉。";
	CHANNEL_D->do_channel(this_object(), "rumor",str);
if(killer->query("tongji/pktime")>=3)
 {
 killer->move("/d/wiz/dalao");
  message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer
->query("name")+"连续杀伤人命，现被关进大牢，待秋后发落！\n"NOR,users());
            }

       	}
	     	bls=10;
		killer->delete_temp("kill_weapon");
		killer->delete_temp("kill_msg");
           } else {    // killer is not user or killer didn't init the kill.
	    //   int i;
	       string last_faint;
	       object fainter;
	       // mon 8/1/98
	       // check who fainted the victim.
	       // if it was a player faint the victim,
	       // give the player credit for pk :)
	       last_faint=victim->query_temp("last_fainted_from");
	       if(last_faint) {
		   fainter=find_player(last_faint);
		   if(fainter && userp(fainter)) {
	             if(!my_killer_list) init_killer=-1;
	             else init_killer=
			 member_array(last_faint, my_killer_list);

		     if(init_killer!=-1) {
                       fainter->apply_condition("no_pk_time",240+
	                 fainter->query_condition("no_pk_time"));
		       log_file("death","["+ctime(time())+"] "+
			       victim->query("id")+" was fainted by "+
			       fainter->query("id")+" and killed by "+
			       killer->query("id")+".\n");
		     }
		   }
	       }

               victim_penalty(victim);

	       bls = 10;
//	       CHANNEL_D->do_channel(this_object(), "rumor",
//		  sprintf("%s被%s杀死了。", victim->name(1), killer->name(1)));
/////////////////for NK rumor

			weapon=killer->query_temp("kill_weapon");
			if(weapon && rkmsg)
			{
	     		str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"用"HIY+weapon->name()+HIM+rkmsg+"死了。";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			} else {
			if(rkmsg && !weapon)
			{
			str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"用一招"+HIW"“"+rkmsg+"”"+HIM"送去了阎罗地府。";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			}else if(weapon && !rkmsg){
			str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"用"HIY+weapon->name()+HIM"送去了阎罗地府。";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
					   }else {
			str=victim->name(1)+"在"+
	         	MISC_D->find_place(environment(killer))+"被"+killer->name(1)+"杀死了。";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
						  }
    if(userp(killer))
{
           if(!victim->query("tongji/fanren")&&vics&&member_array(victim->query("id"),vics)>-1)
	{
	  message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer->name(1)+"无视王法，滥伤人命，打死了"+victim->name(1)+"，现正被官府通缉！\n"+NOR,users());
	  killer->set("tongji/fanren",1);
	  killer->set("tongji/mudage",killer->query("mud_age"));
	  //added for prison
	  killer->add("tongji/pktime",1);
	  killer->delete_temp("kill/target/"+victim->query("id"));
	  str = "听说"+killer->name(1)+"杀了人，正在逃命。";
	  CHANNEL_D->do_channel(this_object(), "rumor",str);
if(killer->query("tongji/pktime")>=3)
 {
 killer->move("/d/wiz/dalao");
  message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer
->query("name")+"连续杀伤人命，现被关进大牢，待秋后发落！\n"NOR,users());
            }

	}
	else if(victim->query("tongji/fanren"))
	{
	message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer->name(1)+"杀死通缉犯"+victim->name(1)+"有功，现通报嘉奖！\n"+NOR,users());
	killer->add("kill/pkgain",gain);
        killer->add("combat_exp",gain);
        killer->add("PKFANREN",1);
	victim->delete("tongji");
        str=chinese_daoxing(gain);
        if(strlen(str)<=1)
	str="零点";
        str=killer->name(1)+"得到了"+str+"道行！";
        str=victim->name(1)+"被"+killer->name(1)+
            "就地正法。"+str;
        CHANNEL_D->do_channel(this_object(), "rumor",str);

       }else if(kils&&member_array(killer->query("id"),kils)>-1)
       {

        str=victim->name(1)+"被"+killer->name(1)+
            "正当防卫杀死了。";
        CHANNEL_D->do_channel(this_object(), "rumor",str);
       }else {

	message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer->name(1)+"失手打死了"+victim->name(1)+"，现已逃命，望知其下落者，速报知官府！\n"+NOR,users());
	killer->set("tongji/fanren",1);
	killer->set("tongji/mudage",killer->query("mud_age"));
	killer->add("tongji/pktime",1);
	//added for prison
	killer->delete_temp("kill/target/"+victim->query("id"));
	str = "听说"+killer->name(1)+"因过失伤人，正被官府通缉。";
	CHANNEL_D->do_channel(this_object(), "rumor",str);
if(killer->query("tongji/pktime")>=3)
 {
 killer->move("/d/wiz/dalao");
  message("channel:xyj",HIR+"【创世通告】薛仁贵(xueren gui)："+killer
->query("name")+"连续杀伤人命，现被关进大牢，待秋后发落！\n"NOR,users());
            }

	  	}
        }
      if(!userp(killer)&&userp(victim)&&victim->query("tongji/fanren"))
   {
          str=victim->name(1)+"被"+killer->name(1)+
            "就地正法。";
        CHANNEL_D->do_channel(this_object(), "rumor",str);
        victim->delete("tongji");
   }
          }
       }
   } else {  //NPC is the victim.
	  if(userp(killer) || killer->is_manmade_npc()) {
                int reward;

		reward=nk_gain(killer, victim);
		// nk_reward is defined as needed for each NPC
		// this allows individual NPC to customize NK reward.
		// mon 12/24/99
		if((int)victim->nk_reward(killer, reward)>0) {
		    // this NPC has its own reward.
		} else if(reward>=0) {
		  string msg;
		  int pot_gain;
		  int exp_gain;
		  int min_gain;
		  int nn;
		  object* team_members;
		  string ttarget_id;
		  team_members = killer->query_team();
		  ttarget_id = killer->query_temp("ttarget");
		  min_gain = reward / 2;
		  exp_gain = min_gain + random( min_gain );
		  reward = min_gain + random( min_gain );
		  pot_gain = random( ( exp_gain + reward) / 10 ) + 1;
		  if ( killer->is_manmade_npc() )
		  	pot_gain *= 2;
          if ( victim->is_manmade_npc() ) {
              int temp_exp_daoxing, temp_qn_factor;
              temp_qn_factor = victim->rzr_reward_factor();
              temp_exp_daoxing = victim->query("combat_exp")/2 + victim->query("daoxing")/2;
              pot_gain += temp_exp_daoxing / 4000 * temp_qn_factor;
              if (userp(killer)) {
				  if (sizeof(team_members) <= 1 || ttarget_id != victim->query("id")) {
                		CHANNEL_D->do_channel(victim, "rumor",killer->name() + "杀死了"
                		     + victim->query("family/family_name") + victim->name()
                   		     + "(" + victim->rzr_get_my_level() + "级), 不但得到巨款和超级装备外, 还得到了"
                   		     + pot_gain + "点潜能");
			  	  } else {
					  CHANNEL_D->do_channel(victim, "rumor",killer->name() + "杀死了"
					      + victim->query("family/family_name") + victim->name()
					      + "(" + victim->rzr_get_my_level() + "级), 不但得到巨款和超级装备外, 他所在的队伍还得到了"
                   		  + ( pot_gain + pot_gain / 10 ) + "点潜能");
				  }
              }
              killer->add("rzr_killed_lvl" + victim->rzr_get_my_level(), 1);
          }
          if ( sizeof(team_members) <= 1 || ttarget_id != victim->query("id")) {
          		killer->add("kill/nkgain",reward);
		  		killer->add("daoxing",reward);
		  		killer->add("combat_exp", exp_gain);
                str=chinese_daoxing(reward);
                if (str == "") str = "0";
                // tell_object(killer,"\n你得到了"+str+"道行。\n");
                // tell_object(killer,"\n你得到了"+exp_gain+"武行。\n");
          		killer->add("potential",pot_gain);
              	if (victim->is_manmade_npc())
			tell_object(killer,"\n你得到了"+pot_gain+"潜能。\n");
		  		msg=sprintf("%s(%s)杀死了%s(%s)，得到%d点道行,%d点潜能和%d点武行。",
		  		killer->query("name"), killer->query("id"),
		    	victim->query("name"), victim->query("id"),reward,pot_gain,exp_gain);
			} else {
				object killer_env;
				int team_total;
				int exp_share, dist_exp;
				int daoxing_share, dist_daoxing;
				int pot_share, dist_pot;
				msg = "队伍杀死了 " + victim->query("family/family_name") + victim->query("name") +
				      "(" + victim->rzr_get_my_level() + "级), 在场的队员:\n";
				killer_env = environment(killer);
				team_total = 0;
				dist_exp = 0;
				dist_daoxing = 0;
				dist_pot = 0;
				for ( nn = 0; nn < sizeof(team_members); nn++) {
					object mate;
					mate = team_members[nn];
					if ( killer_env == environment(mate) && mate->query_temp("ttarget") == ttarget_id ) {
						team_total += ( mate->query("combat_exp") + mate->query("daoxing") ) / 10000;
					}
				}
				for ( nn = 0; nn < sizeof(team_members); nn++) {
					object mate;
					mate = team_members[nn];
					if ( killer_env == environment(mate) && mate->query_temp("ttarget") == ttarget_id
						&& mate != killer ) {
						int my_share;
						my_share = ( ( mate->query("combat_exp") + mate->query("daoxing") ) / 10000 )
						           * 100 / team_total;
						exp_share = exp_gain * my_share / 100;
						daoxing_share = reward * my_share / 100;
						pot_share = pot_gain * my_share / 100;
						dist_exp += exp_share;
						dist_daoxing += daoxing_share;
						dist_pot += pot_share;
          				mate->add("kill/nkgain",daoxing_share);
		  				mate->add("daoxing",daoxing_share);
		  				mate->add("combat_exp", exp_share);
		  				mate->add("potential",pot_share);
		  				mate->delete_temp("ttarget");
						msg += mate->query("name") + "(" + mate->query("id")
						      + ")得到了" + chinese_daoxing(daoxing_share) + "道行, "
						      + pot_share + "点潜能, " + exp_share + "武行\n";
					}
				}
				exp_share = exp_gain - dist_exp;
				daoxing_share = reward - dist_daoxing;
				pot_share = pot_gain - dist_pot + pot_gain / 10; // the person who killed npc will get extra 1/10
				pot_gain += pot_gain / 10;
				killer->add("kill/nkgain",daoxing_share);
				killer->add("daoxing",daoxing_share);
				killer->add("combat_exp", exp_share);
				killer->add("potential",pot_share);
				killer->delete_temp("ttarget");
				msg += "最后一击者 - " + killer->query("name") + "(" + killer->query("id") +
				       ")得到了" + chinese_daoxing(daoxing_share) + "道行, "
						      + pot_share + "点潜能, " + exp_share + "武行\n";
				msg += "队伍获得总数: " + chinese_daoxing(reward) + "道行, "
						      + pot_gain + "点潜能, " + exp_gain + "武行\n";
				message_vision(msg, killer);
			}

		  if ( userp(victim) && killer->is_manmade_npc())
		  	log_file("rzr_kill_player","["+ctime(time())+"] "+msg+"\n");
		  else if ( victim->is_manmade_npc())
		  	log_file("rzr_killed","["+ctime(time())+"] "+msg+"\n");
		  else if ( killer->is_manmade_npc() )
		  	log_file("rzr_kill","["+ctime(time())+"] "+msg+"\n");
		  else
		  	log_file("npc_kill","["+ctime(time())+"] "+msg+"\n");
		  CHANNEL_D->do_channel(this_object(), "sys",msg);
		}
	  }
	  killer->add("MKS", 1);
	  bls = 1;
	}

        if(!userp(killer) &&
	   ((killer->query("daoxing")+killer->query("combat_exp"))/10>
	    (victim->query("daoxing")+victim->query("combat_exp"))) ) bls=0;
        //mon 2/15/98
	//can't use newbie to kill NPC to increase NPC's bls.

	// NPC got 10 times of bellicosity than user.
	killer->add("bellicosity", bls * (userp(killer)? 1: 10));

	if( stringp(vmark = victim->query("vendetta_mark")) )
		killer->add("vendetta/" + vmark, 1);

        if(userp(killer)) killer->save();
	if(userp(victim)) victim->save();
}
void victim_penalty(object victim)
{
    // by snowcat 2/21/1998 for death/*
    int combat_exp_loss = (int)victim->query("combat_exp") / 40;
    int dx_loss = (int)victim->query("daoxing") / 40;

        victim->set("death/mud_age",victim->query("mud_age"));
        victim->set("death/combat_exp_loss",combat_exp_loss);
        victim->set("death/dx_loss",dx_loss);
    log_file("death",victim->query("id")+
      " lost "+combat_exp_loss+" exp points and "
      + dx_loss+ " dx points.\n");

    victim->add("combat_exp", -combat_exp_loss);
    victim->add("daoxing", -dx_loss);
    victim->delete("vendetta");
    if( victim->query("thief") )
        victim->set("thief", (int)victim->query("thief") / 2);
    if( (int)victim->query("potential") > (int)victim->query("learned_points")) {
	int pot_loss;
	pot_loss = ((int)victim->query("learned_points") - (int)victim->query("potential"))/2;
        victim->add("potential", pot_loss);
	victim->set("death/potential_loss",-pot_loss);
    }
        if(random(100)>(int)victim->query_kar()) {
          victim->set("death/skill_loss",1);
      victim->skill_death_penalty();
    } else
      victim->set("death/skill_loss",0);

        victim->save();
}

int nk_gain(object killer, object victim)
{
        string fam, fam1;
        int cla, eff_dx, eff1, eff2, dx, reward, nkgain;

        // some NPC has no rewards.
        // mon 3/9/99
        if(victim->query("no_nk_reward")) return 0;

            //can't kill NPCs which were fainted by
        //other players to get daoxing.
            if(victim->query_temp("last_fainted_from")
               && victim->query_temp("last_fainted_from")!=
               killer->query("id")) return 0;

            fam=killer->query("family/family_name");

        if((fam && !undefinedp(family[fam])) || killer->is_manmade_npc()) {//player must have a
                                             //family.
              cla=family[fam];
              eff_dx=victim->query("eff_dx");
          nkgain=victim->query("nkgain");

              //can't kill NPCs of the same menpai as the player
          //to get daoxing.
          fam1=victim->query("family/family_name");
          if(fam1 && fam==fam1 && !killer->is_manmade_npc() )
            return 0;

              if(eff_dx!=0 && cla*eff_dx>0)
            return 0;
        //for NPC being set eff_dx, only
        //if cla*eff_dx<=0 (not all in xian or all in yao)
        //can gain daoxing.

              //For NPC which has not been set eff_dx,
          //the default is everyone can kill them to get
          //dx reward, however, the default value is low.
          if(!eff_dx) {
            //default value for eff_dx and nkgain.
        //the default nkgain is low.
        //If want to increase the value for certain NPC,
        //then need to set its eff_dx and nkgain.

                int dxn=0;

        eff_dx=(victim->query("daoxing")+
            victim->query("combat_exp"))/2;
                if(eff_dx>20000)
          dxn=eff_dx/3;
        else if(eff_dx>5000)
          dxn=eff_dx/2;
                else
          dxn=eff_dx;
          //make it easier for newbie.
                eff_dx=dxn;
              }

          if(!nkgain) {
            int effdx=eff_dx;

        if(effdx<0) effdx=-effdx;

        if(effdx>667000)
          nkgain=600;
                else if(effdx>333000)
          nkgain=500;
                else if(effdx>100000)
          nkgain=400;
                else if(effdx>33000)
          nkgain=300;
                else if(effdx>17000)
          nkgain=200;
                else if(effdx>5000)
          nkgain=150;
                else if(effdx>2000)
          nkgain=100;
                else if(effdx>500)
          nkgain=50;
                else nkgain=25;

        nkgain=nkgain+20;
          }

                if(eff_dx<0) eff_dx=-eff_dx;
                eff1=eff_dx/8;
        eff2=eff_dx/4;
        dx=(killer->query("daoxing")+
            killer->query("combat_exp"))/2;
        reward = 1;
        if(dx>eff_dx) reward=1;
        else if(dx>eff2) reward=nkgain;
        else if(dx>eff1) reward=10*(dx-eff1)/(eff2-eff1)*
          nkgain/10;
                else reward=1;

        if(cla==0 || (cla!=0 && !fam1)) reward=reward*2/3;
        //cla==0: people not xian and not yao. e.g. longgong, moon.
        //cla!=0: people either xian or yao. if they kill
        //        no family NPC, dx reward reduse.

        if (reward <=1) reward = 1;
        if ( killer->is_manmade_npc())
        	reward *= random( killer->query_int() * killer->query_int() / 10);
        else {
	/* do not give too many nk gains
            int extra_reward;
            int my_exp_dx;
            extra_reward = random(killer->query_int() * killer->query_int() / 200)
                         + random(killer->query_int() * killer->query_int() / 100);
            my_exp_dx = killer->query("combat_exp")/2 + killer->query("daoxing")/2;
            my_exp_dx = my_exp_dx / 10000000;
            if ( my_exp_dx >= 3 ) {
                extra_reward = extra_reward / ((my_exp_dx - 2) * 3);
                if ( random( my_exp_dx ) >= 1 )
                    extra_reward = extra_reward / my_exp_dx;
            }
            reward = reward + extra_reward;
	*/
        }
          // manmade npc should gain more
        if ( reward < 45000 && killer->is_manmade_npc() ) {
			reward = 45000;
		}
        if ( killer->is_manmade_npc() && killer->rzr_need_to_die() )
		reward = 100;
	if ( reward > 100000 )
		reward = 100000;
        return reward;

            }
        return 0;
}

int victim_lose(object killer,object victim,string killerid)
{            int lose,exp_k,exp_v;
             int lose1;

             if((wizardp(victim)&&!wizardp(killer))
            ||(!wizardp(victim)&&wizardp(killer)))
        return 0;

             if(victim->query_temp("last_fainted_from")
               && victim->query_temp("last_fainted_from")!=
               killerid) {
               lose=0;
             } else {
               exp_k=killer->query("daoxing");
               exp_v=victim->query("daoxing");
               if (exp_k>exp_v) {
                 lose=10*exp_v/(exp_k+1)*(4000+exp_v)/500;
          // a exp_v/exp_k pre-factor.
         if(exp_k>exp_v*4) lose=0;
         // if less then 1/4 dx, then no damage.
               } else {
                 lose=(4000+exp_v)/50;  // about 2% lose for victim.
               }
               if(lose<0) lose=0;
               if(lose>exp_v) lose=exp_v;
             }

         // this is the maximum lose.
         lose1=(int)victim->query("daoxing") / 40;
         if(lose>lose1) lose=lose1;

         return lose;
}

string chinese_daoxing(int gain)
{            int year,day,hour;
             string str;

             year=gain/1000;
             day=(gain-year*1000)/4;
             hour=(gain-year*1000-day*4)*3;
             str="";
             if(year) str=str+chinese_number(year)+"年";
             if(day) str=str+chinese_number(day)+"天";
             if(hour) str=str+chinese_number(hour)+"时辰";

             return str;
}

int check_family(string fam)
{
    if(fam && !undefinedp(family[fam]))
      return family[fam];
    else
      return 0;
}


//the following functions are for performs...weiqi
//copy and modified from spelld.c

int attacking_perform_success(object attacker, object target, int skill_level, int success_adj)
{
        int success;
        float ap, dp, f_skill;

        f_skill = 0.0 + skill_level;
        ap = ( f_skill * f_skill * f_skill / 10 ); //this is from skill.
        //at high exp, the skill level can not follow, so need adjustment here.
        ap = ap*(1+attacker->query("combat_exp")/500000);
        ap = ap+attacker->query("combat_exp");
        dp = target->query("combat_exp");

        success = 0;

        if ( success_adj < 20 ) success_adj = 20;
        else if( success_adj > 500 ) success_adj = 500;

        ap = ap*success_adj/100;

        if( random(100)>dp*100/(ap+dp) ) success = 1;

        return success;
}

int attacking_perform_damage(object attacker, object target, int damage_adj)
{
        int a_neili, d_neili, damage;

        if( damage_adj < 50 ) damage_adj = 50;
        else if( damage_adj > 200 ) damage_adj = 200;

        //will use current neili...but do not allow it exceeds 2 time of the max.
        a_neili = attacker->query("force");
        if( a_neili > 2*attacker->query("max_force") ) a_neili = 2*attacker->query("max_force");
        d_neili = target->query("force");
        if( d_neili > 2*target->query("max_force") ) d_neili = 2*target->query("max_force");


        //neili and qi. weaker than cast here...
        damage = (a_neili - d_neili)/30 +
                random(attacker->query("eff_kee") / 30)-random(target->query("eff_kee") / 30);

        //mana_factor, here the attacker has some advantage.
        //the damage_adj higher, the better for attacker.
        damage += (3*damage_adj/200) //weaker than cast here...
                *( attacker->query("force_factor") - random(target->query("force_factor")) );

        //for backfire, we need let it be serious...
        if( damage < 0 ) damage = damage - target->query("force_factor");
        //here increase the damage, since previously it's included in random()

        damage = damage*damage_adj/100; //last damage scaled again.

        //finally, we need let the force level useful...
        //the setting is, at enabled level 200, the damage will double.
        if( damage > 0 )
        {
                damage += (damage*(int)attacker->query_skill("force"))/200;
        }
        else if ( damage < 0 )
        {
                damage += (damage*(int)target->query_skill("force"))/200;
        }


        return damage;
}

/*
weiqi 981206
attacking-cast...called from spells function.
modified for perform...
a typical call would be:

        COMBAT_D->attacking_perform(
                me,
                        //attacker
                target,
                        //target
        skill_level,
            //level of skill used
                success_adj,
                        //success adjustment
                damage_adj,
                        //damage adjustment
                "both",
                        //damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
                HIC "$N几个指头迅速捻动，突然张嘴一喷！红橙黄三道火焰呼！地一声向$n卷去！\n" NOR,
                        //initial message
                HIC "结果$n被烧得焦头烂额！\n" NOR,
                        //success message
                HIC "但是$n轻轻一跳就躲了开来。\n" NOR,
                        //fail message
                HIC "但是火焰被$n以法力一逼，反向$N回卷而去！\n" NOR,
                        //backfire initial message
                HIC "结果太乙真火反噬，$n被烧得焦头烂额！\n" NOR
                        //backfire hit message. note here $N and $n!!!
        );
*/
void attacking_perform(
        object attacker,
        object target,
    int skill_level,//the level of skill used to attack.
        int success_adj,
        int damage_adj, //default value is 100 for this 2 parameters.
        string damage_type, //must be "shen"/"sen", "qi"/"kee" or "both"(default)
        string msg_init,
        string msg_success,
        string msg_fail,
        string msg_backfire_init,
        string msg_backfire_success)
{
        int damage;

        //first, show the initial message...
        message_vision( msg_init, attacker, target );

        //calculate if the casting can happen...
        if( attacking_perform_success(attacker, target, skill_level, success_adj) == 0 )
        {
                message_vision( msg_fail, attacker, target );
                //let the target kill attacker.
                target->kill_ob(attacker);
                return;
        }

        damage = attacking_perform_damage(attacker, target, damage_adj);

        if( damage > 0 ) //attacker hit target
                SPELL_D->apply_damage(attacker, target, damage, damage_type, msg_success);

        else if( damage < 0 ) //backfire
        {
                message_vision(msg_backfire_init, attacker, target);
                SPELL_D->apply_damage(target, attacker, -damage, damage_type, msg_backfire_success);
        }

        else //damge=0
        message_vision(HIB "结果正好被$N以内力逼住，谁也没有吃亏。\n" NOR, target);

        //let the target kill attacker.
        target->kill_ob(attacker);

        return;
}

int do_attack_damage(object me, object victim, object weapon)//调动此函数，相当于直接打中敌人，敌人一样会受到伤害
{

        mapping my, your, action, victim_action;
	string  result;
	string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
	mixed foo;
	int damage, damage_bonus, defense_factor;
	result="";
my = me->query_entire_dbase();
your = victim->query_entire_dbase();
action = me->query("actions");
damage = me->query_temp("apply/damage");
damage = (damage + random(damage)) / 2;
if( action["damage"] )
        damage += action["damage"] * damage / 100;

	damage_bonus = me->query_str();

	// Let force skill take effect.
	if( my["force_factor"] && (my["force"] > my["force_factor"]) ) {
	if( force_skill = me->query_skill_mapped("force") ) {
			foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["force_factor"]);
			if( stringp(foo) ) result += foo;
				else if( intp(foo) ) damage_bonus += foo;
				}
			}

			if( action["force"] )
				damage_bonus += action["force"] * damage_bonus / 100;

			if( martial_skill = me->query_skill_mapped(attack_skill) ) {
				foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}

			// Let weapon or monster have their special damage.
			if( weapon ) {
				foo = weapon->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			} else {
				foo = me->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo * 3 / 4;
			}

			if( damage_bonus > 0 )
				damage += (damage_bonus + random(damage_bonus))/2;
			if( damage < 0 ) damage = 0;

			// Let combat exp take effect
			defense_factor = your["combat_exp"];
			while( random(defense_factor) > my["combat_exp"] ) {
				damage -= damage / 3;}


                    damage = victim->receive_damage("kee", damage, me );

			if( (me->is_killing(victim) || weapon)
			&& random(damage) > (int)victim->query_temp("apply/armor") ) {
				// We are sure that damage is greater than victim's armor here.
				victim->receive_wound("kee",
					damage - (int)victim->query_temp("apply/armor"), me);
				//wounded = 1;
				}
			return damage;
}
