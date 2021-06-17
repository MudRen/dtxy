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
mapping family=(["����ɽ���Ƕ�":1,
                 "��ɽ��":1,
				 "ˮ�¹�":1,
				 "�Ϻ�����ɽ":1,
                 "��ׯ��":1,
                 "���޵ظ�":-1,
                 "�¹�":1,
                 "��������":1,
                 "��ѩɽ":-1,
                 "�ݿ�ɽ�޵׶�":-1,
                 "��˿��":-1,
                 "������":1,
                 "����ɢ��":-1,
                 "����ɽ���鶴":1,
                 "���ƶ�":-1,
/*
				 "�Ϻ�����ɽ":1,
                 "������":1,
                 "��ׯ��":1,
                 "���޵ظ�":0,
                 "�¹�":0,
                 "��������":0,
                 "����":0,
                 "��ѩɽ":-1,
                 "����ɽ�Ž���":-1,
                 "�ݿ�ɽ�޵׶�":-1,
                 "��ʯɽ�̲�̶":-1,
                 "���ƶ�":-1,
*/
]);

string *guard_msg = ({
    CYN "$Nע����$n���ж�����ͼѰ�һ�����֡�\n" NOR,
    CYN "$N������$n��һ��һ������ʱ׼���������ơ�\n" NOR,
    CYN "$N�������ƶ��Ų�����Ҫ�ҳ�$n��������\n" NOR,
    CYN "$NĿ��ת���ض���$n�Ķ�����Ѱ�ҽ��������ʱ����\n" NOR,
    CYN "$N�������ƶ��ŽŲ����Ż����֡�\n" NOR,
});

string *catch_hunt_msg = ({
    HIW "$N��$n������������ۺ죬���̴���������\n" NOR,
    HIW "$N����$n��ȣ����ɶ������㣡��\n" NOR,
    HIW "$N��$nһ���棬������˵�ʹ���������\n" NOR,
    HIW "$Nһ��Ƴ��$n�����ߡ���һ�����˹�����\n" NOR,
    HIW "$Nһ����$n�����һ㶣���У����������㣡��\n" NOR,
    HIW "$N�ȵ�����$n�����ǵ��ʻ�û���꣬���У���\n" NOR,
    HIW "$N�ȵ�����$n�����У���\n" NOR,});

string *winner_msg = ({
    CYN "\n$N������Ц��˵���������ˣ�\n\n" NOR,
    CYN "\n$N˫��һ����Ц��˵�������ã�\n\n" NOR,
    CYN "\n$Nʤ�����У����Ծ�����ߣ�Ц�������ã�\n\n" NOR,
    CYN "\n$n��ɫ΢�䣬˵��������������\n\n" NOR,
    CYN "\n$n������˼�����˵�����ⳡ�����������ˣ�����������\n\n" NOR,
    CYN "\n$n���һ�ݣ�������Ҿ˵�����������ղ�������Ȼ������\n\n" NOR,
});

void create()
{
    seteuid(getuid());
    set("name", "ս������");
    set("id", "combatd");
}

string damage_msg(int damage, string type)
{
    string str;

//  return "��� " + damage + " ��" + type + "��\n";

    if( damage == 0 ) return "���û������κ��˺���\n";

    switch( type ) {
    case "����":
    case "ץ��":
    case "����":
        if( damage < 10 ) return "���ֻ������ػ���$p��Ƥ�⡣\n";
        else if( damage < 20 ) return "�����$p$l����һ��ϸ����Ѫ�ۡ�\n";
        else if( damage < 40 ) return "������͡���һ������һ���˿ڣ�\n";
        else if( damage < 80 ) return "������͡���һ������һ��Ѫ���ܵ��˿ڣ�\n";
        else if( damage < 160 ) return "������͡���һ������һ���ֳ�������˿ڣ�����$N������Ѫ��\n";
        else return "���ֻ����$nһ���Һ���$p��$l������һ������ǵĿ����˿ڣ�\n";
        break;
    case "����":
    case "����":
        if( damage < 10 ) return "���ֻ����$n��Ƥ�����������������Ӷ���ࡣ\n";
        else if( damage < 20 ) return "�����$n$l����һ��ϸ����Ѫ�ۡ�\n";
        else if( damage < 40 ) return "��������͡�һ������һ��Ѫ���ܵ��˿ڣ�\n";
        else if( damage < 80 ) return "���ֻ�����ۡ���һ����$n��$l������Ѫ��Ȫӿ��ʹ��$pҧ���гݣ�\n";
        else if( damage < 160 ) return "������ۡ���һ������һ���ֳ�������˿ڣ�����$N������Ѫ��\n";
        else return "���ֻ����$nһ���Һ���$p��$l������һ������ǵĿ����˿ڣ�\n";
        break;
    case "ǹ��":
    case "����":
        if( damage < 10 ) return "���ֻ������ش���$p��Ƥ�⡣\n";
        else if( damage < 20 ) return "�����$p$l�̳�һ�����ڡ�\n";
        else if( damage < 40 ) return "������ۡ���һ��������$n$l����\n";
        else if( damage < 80 ) return "������ۡ���һ���̽�$n��$l��ʹ$p�������������˲���\n";
        else if( damage < 160 ) return "��������͡���һ����$w����$p$l�̳�һ��Ѫ��ģ����Ѫ������\n";
        else return "���ֻ����$nһ���Һ���$w����$p��$l�Դ���������Ѫ�������أ�\n";
        break;
    case "����":
        if( damage < 10 ) return "���ֻ�������һ������$n��Ƥ��������һ��׺ۡ�\n";
        else if( damage < 20 ) return "�����$p��$l���¼���Ѫ�ۡ�\n";
        else if( damage < 40 ) return "���һ�������У�$n��$l��ʱ���ּ���Ѫ�ף�\n";
        else if( damage < 80 ) return "���һ�������У�$n����Ѫ����ע��\n";
        else if( damage < 120 ) return "������꡹��һ����$n��ʱ��Ѫ�ɽ���\n";
        else if( damage < 160 ) return "�����һ�¡��꡹��һ����$n�����û�����Ѫ��\n";
        else return "������꡹���ص����У�$n������ǧ���׿ף�Ѫ���Ĵ���ɣ�\n";
        break;
    case "����":
    case "ȭ��":
    case "����":
        if( damage < 10 ) return "���ֻ����������������Ĳ�Ӭ��΢���˵㡣\n";
        else if( damage < 20 ) return "�����$p��$l���һ�����ࡣ\n";
        else if( damage < 40 ) return "���һ�����У�$n��$l��ʱ����һ���ϸߣ�\n";
        else if( damage < 80 ) return "���һ�����У�$n�ƺ���һ����Ȼ���˲�С�Ŀ���\n";
        else if( damage < 120 ) return "������项��һ����$n����������\n";
        else if( damage < 160 ) return "�����һ�¡��项��һ�����$n�����˺ü�������һ��ˤ����\n";
        else if( damage < 240 ) return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n";
        else return "���ֻ�������项��һ�����죬$n��һ�����ݰ���˳�ȥ��\n";
        break;
    case "ײ��":
    case "����":
        if( damage < 10 ) return "���ֻ����������������ڸ�$nɦ��һ������\n";
        else if( damage < 20 ) return "�����$p��$l�ҳ�һ��С������\n";
        else if( damage < 40 ) return "����Ҹ����ţ�$n��$l��ʱ����һ���ϸߣ�\n";
        else if( damage < 80 ) return "����Ҹ����ţ�$n�ƺ�һ����Ȼ���˲�С�Ŀ���\n";
        else if( damage < 120 ) return "������项��һ����$n�۵����������ˣ�\n";
        else if( damage < 160 ) return "�����һ�¡��䡹��һ���ҵ�$n��ð���ǣ���һ��ˤ����\n";
        else if( damage < 240 ) return "������ص����У�$n��ǰһ�ڣ����ۡ���һ���³�һ����Ѫ��\n";
        else return "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã�\n";
        break;
    case "����":
    case "����":
        if( damage < 20 ) return "�����$n����һ�����ţ����ڸ�$nɦ��һ������\n";
        else if( damage < 40 ) return "���$n����һ�Σ����˵�С����\n";
        else if( damage < 80 ) return "���$n��Ϣһ�ϣ���Ȼ�е����������\n";
        else if( damage < 120 ) return "���$n����һ���ʹ�����������˲��ᣡ\n";
        else if( damage < 160 ) return "������ˡ���һ��$nֻ������ǰһ�ڣ�˫��������ֹ��\n";
        else return "���ֻ�������ˡ���һ�����죬$n���ۡ���һ���³�һ����Ѫ����������������λ��\n";
        break;
        case "����":
        case "����":
        if( damage < 10 ) return "���ֻ����$n��Ƥ�����������������Ӷ���ࡣ\n";
        else if( damage < 20 ) return "�����$n$l���һ����΢���Ϻۡ�\n";
        else if( damage < 40 ) return "�����ž����һ����$n$l���һ��������Ѫ�ۣ�\n";
        else if( damage < 80 ) return "���ֻ����ž����һ����$n��$l�����Ƥ��������ʹ��$pҧ���гݣ�\n";
        else if( damage < 160 ) return "�����ž����һ�����죡��һ�º�������ֻ���$nƤ��������Ѫ���ɽ���\n";
        else return "���ֻ����$nһ���Һ���$w���صس�����$p��$l��$n��ʱѪ���ɣ�ʮ�����˾�����\n";
        break;
    default:
        if( !type ) type = "�˺�";
        if( damage < 10 ) str =  "���ֻ����ǿ���һ����΢";
        else if( damage < 20 ) str = "��������΢��";
        else if( damage < 30 ) str = "������һ��";
        else if( damage < 50 ) str = "������һ������";
        else if( damage < 80 ) str = "��������Ϊ���ص�";
        else if( damage < 120 ) str = "�������൱���ص�";
        else if( damage < 170 ) str = "������ʮ�����ص�";
        else if( damage < 230 ) str = "�����ɼ������ص�";
        else str =  "�����ɷǳ����µ�����";
        return str + type + "��\n";
    }
}

string eff_status_msg(int ratio)
{
    if( ratio==100 ) return HIG "��������Ѫ��ӯ����û�����ˡ�" NOR;
    if( ratio > 95 ) return HIG "�ƺ����˵����ˣ��������������������" NOR;
    if( ratio > 90 ) return HIY "�������������˵����ˡ�" NOR;
    if( ratio > 80 ) return HIY "���˼����ˣ������ƺ��������¡�" NOR;
    if( ratio > 60 ) return HIY "���˲��ᣬ������״������̫�á�" NOR;
    if( ratio > 40 ) return HIR "��Ϣ���أ�������ʼɢ�ң��������ܵ�����ʵ���ᡣ" NOR;
    if( ratio > 30 ) return HIR "�Ѿ��˺����ۣ���������֧���Ų�����ȥ��" NOR;
    if( ratio > 20 ) return HIR "�����൱�ص��ˣ�ֻ�»�������Σ�ա�" NOR;
    if( ratio > 10 ) return RED "����֮���Ѿ�����֧�ţ��ۿ���Ҫ���ڵ��ϡ�" NOR;
    if( ratio > 5  ) return RED "���˹��أ��Ѿ�����һϢ�����ڵ�Ϧ�ˡ�" NOR;
    return RED "���˹��أ��Ѿ�������в�����ʱ�����ܶ�����" NOR;
}

string status_msg(int ratio)
{
    if( ratio==100 ) return HIG "����������������һ��Ҳ���ۡ�" NOR;
    if( ratio > 95 ) return HIG "�ƺ���Щƣ����������Ȼʮ���л�����" NOR;
    if( ratio > 90 ) return HIY "������������Щ���ˡ�" NOR;
    if( ratio > 80 ) return HIY "�����ƺ���ʼ�е㲻̫��⣬������Ȼ�������ɡ�" NOR;
    if( ratio > 60 ) return HIY "�������꣬������״������̫�á�" NOR;
    if( ratio > 40 ) return HIR "�ƺ�ʮ��ƣ����������Ҫ�ú���Ϣ�ˡ�" NOR;
    if( ratio > 30 ) return HIR "�Ѿ�һ��ͷ�ؽ����ģ������������֧���Ų�����ȥ��" NOR;
    if( ratio > 20 ) return HIR "�������Ѿ����������ˡ�" NOR;
    if( ratio > 10 ) return RED "ҡͷ���ԡ�����бб��վ��վ���ȣ��ۿ���Ҫ���ڵ��ϡ�" NOR;
    return RED "�Ѿ���������״̬����ʱ������ˤ����ȥ��" NOR;
}

//report_shen messages
string sen_status_msg(int ratio)
{
    if( ratio==100 ) return HIG "������ͷ�����ѣ�һ��Ҳ���Ժ���" NOR;
    if( ratio > 90 ) return HIG "�������Լ����Դ����ƺ��е㲻̫�þ���" NOR;
    if( ratio > 80 ) return HIY "��������Щ�Ժ��ˡ�" NOR;
    if( ratio > 60 ) return HIY "��ȷ�е��Ժ��ˣ�������ó������ϱ���" NOR;
    if( ratio > 40 ) return HIR "���۷�ֱ���ڽ����ѣ����ǿ�ʼ���ҡ�" NOR;
    if( ratio > 20 ) return HIR "���Ժ�����ҡҡ�λΣ��Ѿ��治�������ϱ��ˡ�" NOR;
    if( ratio > 10 ) return RED "�����Ѿ����ڼ��Ȼ����С�" NOR;
    return RED "�����Ѿ���ȫ��ʧ����ʱ���п��ܱ�����ȥ��" NOR;
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
    result = "\n" + action["action"] + "��\n";

    //ȡ��me��ʲô����������
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

       //(2) ���������ڹ��ķ������� added by yeahsi
       if ( victim->query_temp("jldl") && living(victim) )       //�������������jldl,���Ҳ����ε�
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

                        	//if (me->query_temp("ldlh")) result = "\n" + action["action"] + "��\n";
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
			CHANNEL_D->do_channel(victim, "rumor",me->name()+"����"+victim->name()+"�Ĳ�ת��ʽ֮�����Լ����Լ������ˡ�");
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
			debug_msg = GRN "AP��" + (ap/100) + "��DP��" + (dp/100) + "��PP��" + (pp/100)
			            + "��Mod��" + (mod_val/100);
        	if( damage > 0 )
                	tell_object(me, debug_msg + "���˺�����" + damage + NOR + "\n");
        	else
                	tell_object(me, debug_msg + NOR + "\n");
        }

           // condition added to avoid null point exception
        if( victim && objectp(victim) && wizardp(victim) && (string)victim->query("env/combat")=="verbose" )
        {
			string debug_msg;
			debug_msg = GRN "AP��" + (ap/100) + "��DP��" + (dp/100) + "��PP��" + (pp/100)
			            + "��Mod��" + (mod_val/100);
        	if( damage > 0 )
                	tell_object(victim, debug_msg + "���˺�����" + damage + NOR + "\n");
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
                        	message_vision(CYN + "$N���Ʋ����ˣ���$nչ������������"+NOR, me, victim);
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
	        	message_vision("$Nһ�����У�¶����������\n", me);
	            	do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
	        }
	        else
	        {
	        	message_vision("$N��$n����ʧ�󣬳û�����������\n", victim, me);
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
		msg_head = "ֻ��$N����" + weapon->query("name");
	else
	{
		msg_head = "ֻ��$N������˫��ʩչ��";
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
				msg = HIY + msg_head+HIY"ʹ��";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIY"���������һ�������������$n��������һ��������\n"+ NOR;
							break;
						case 1:
							msg += HIY"�����������һ֧��ɫ������$n���Ϲᴩ������\n"+ NOR;
							break;
						case 2:
							msg += HIY"������������һ�ѽ�ɫ������$n������������ɼ��ǵ��˿ڣ�\n"+ NOR;
							break;
						case 3:
							msg += HIY"��������������ɫ������$n���ñ������ˣ�\n"+ NOR;
							break;
						case 4:
							msg += HIY"����ӥ�������ӥ�����������$n�ĵñ������ˣ�\n"+ NOR;
							break;
						case 5:
							msg += HIY"����Ԫ�ط籩�����񱩵Ľ�Ԫ�ؽ�$n�߸�����Ȼ��$n���ص����ڵ��ϣ�\n"+ NOR;
							break;
						case 6:
							msg += HIY"��ʥ����������ɫ��ʥ����$n��������˾޴���˺���\n"+ NOR;
							break;
						case 7:
							msg += HIY"����ҫ��ء������޾���ʥ����ҫ�£�$n��û��˿��������������\n"+ NOR;
							break;
						case 8:
							msg += HIY"������֮ŭ�����������ʹ$N����������ֻ��ɫ������$n���ڵأ�ֻ֪����ͣ��Ĥ�ݣ�\n"+ NOR;
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
					msg += HIY"��ϵ����, ˭֪$n��װ���Զ�����һ����������ɵ�ס��$N�Ĺ�����\n"NOR;
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
					msg += HIY"��ϵ����, ˭֪$N�Ŀ���ʵ�ڲ����Ȼ�����ˣ�\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 1:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIB + msg_head+HIB"ʹ��";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIB"��������������$n���³���һ�����У����ϵ�����$n��������\n"+ NOR;
							break;
						case 1:
							msg += HIB"��ӿȪ������������Ϣ��Ȫˮ�Ӷ���$n��������\n"+ NOR;
							break;
						case 2:
							msg += HIB"����¶������ˮ������������$n����Χ��$n��֪�������ж���û����ˣ�\n"+ NOR;
							break;
						case 3:
							msg += HIB"����ɱ����������������ˮ�ζ�����$n�����壬��ӡ��$n��������\n"+ NOR;
							break;
						case 4:
							msg += HIB"��ˮʴ����������ڤ��ĸ�ʴ֮ˮ����ʴ��$n�����壬������$n��������\n"+ NOR;
							break;
						case 5:
							msg += HIB"��ˮԪ�ط籩�����񱩵�ˮԪ�ؽ�$n��Ķ������ᣡ\n"+ NOR;
							break;
						case 6:
							msg += HIB"��ˮ��������һ����Ө��ˮ���ڿն����³�һ��ˮ����$n�����ڵأ�\n"+NOR;
							break;
						case 7:
							msg += HIB"������ˮ������һ�������ı����ڿն���$n�����������������ߣ�ҫ�۵Ĺ�â��ס�ˣ�\n"+ NOR;
							break;
						case 8:
							msg += HIB"��Ů��֮�᡻��˾��������Ů��������������ˮ��$n���ڵأ�Ҫ���������ף�\n"+ NOR;
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
					msg += HIB"ˮϵ����, ˭֪$n��װ���Զ�����һ����������ɵ�ס��$N�Ĺ�����\n"NOR;
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
					msg += HIB"ˮϵ����, ˭֪$N�Ŀ���ʵ�ڲ����Ȼ�����ˣ�\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 2:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIG + msg_head+HIG"ʹ��";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIG"������������һ�����ٴ�$n���������$n������һ�£�������Щ���Ծ���\n"+ NOR;
							break;
						case 1:
							msg += HIG"��������������ڵ����٣�ɢ������ɫ����Ϣ��$n����һЩ��������Щί�Ҳ����ˣ�\n"+ NOR;
							break;
						case 2:
							msg += HIG"������������һ��������$n���������$n������һ�£�������Щ���Ծ���\n"+ NOR;
							break;
						case 3:
							msg += HIG"�������󡻣������ľ����ӵ����������$n��ס��$n�Ե��ķ������ˣ�\n"+ NOR;
							break;
						case 4:
							msg += HIG"����ľ������һ���ޱȾ޴��ľͷ��������$nͷ�ϣ�$n��ʱ���ǲ����ˣ�\n"+ NOR;
							break;
						case 5:
							msg += HIG"��ľԪ�ط籩�����񱩵�ľԪ�ش���$n�ֲ������������ˣ�\n"+ NOR;
							break;
						case 6:
							msg += HIG"������������$n���ܵ�ֲ�￪ʼ������������$nŪ���ۻ����ң�\n"+NOR;
							break;
						case 7:
							msg += HIG"������֮�ġ������д���Ȼ����֮���ľ��飬�����Ǵ��������齫$n����л���\n"+ NOR;
							break;
						case 8:
							msg += HIG"�����������ɡ�������ڵ��µ����ӣ��������������з�ѿ�ɳ����������ֲ��ӵ��������$n����ȫ�����ˣ�\n"+ NOR;
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
					msg += HIG"ľϵ����, ˭֪$n��װ���Զ�����һ����������ɵ�ס��$N�Ĺ�����\n"NOR;
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
					msg += HIG"ľϵ����, ˭֪$N�Ŀ���ʵ�ڲ����Ȼ�����ˣ�\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 3:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIR + msg_head+HIR"ʹ��";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += HIR"���û�������$nһ��С�ı�һ���������У���ʱ��Щͷ�ؽ��ᣡ\n"+ NOR;
							break;
						case 1:
							msg += HIR"������������һ�����ȵĻ������$n����$n��������һ�����ڵĿ�����\n"+ NOR;
							break;
						case 2:
							msg += HIR"���������������ȵĻ���ȼ��������$n���챻�����ˣ�\n"+ NOR;
							break;
						case 3:
							msg += HIR"��������������ѹ���Ļ�����$n��߱�ը��$n��ը��Ѫ��ģ����\n"+ NOR;
							break;
						case 4:
							msg += HIR"���������������Ե����Ļ���ȼ��������$n�������Ժ��ˣ�\n"+ NOR;
							break;
						case 5:
							msg += HIR"����Ԫ�ط籩�����񱩵Ļ�Ԫ�ؽ�$n���˸����ڣ�\n"+ NOR;
							break;
						case 6:
							msg += HIR"���������衻��һ��������ɵķ�������$n��ȥ��$n���Ż��ˣ�\n"+NOR;
							break;
						case 7:
							msg += HIR"����ζ��𡻣���ؼ������Ļ��棬ȼ����$n��֫�壬ȼ����$n�ķ�����\n"+ NOR;
							break;
						case 8:
							msg += HIR"������֮�衻����������飬����Ļ���֮�裬��ȫ������$n����꣡\n"+ NOR;
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
					msg += HIR"��ϵ����, ˭֪$n��װ���Զ�����һ����������ɵ�ס��$N�Ĺ�����\n"NOR;
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
					msg += HIR"��ϵ����, ˭֪$N�Ŀ���ʵ�ڲ����Ȼ�����ˣ�\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 4:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = YELGRN + msg_head+YELGRN"ʹ��";
				if(wuxing_damage>0)
				{
					switch(random(level))
					{
						case 0:
							msg += YELGRN"������������$nһ��С�ĵ�����һ���޴���ѷ��\n"+ NOR;
							break;
						case 1:
							msg += YELGRN"����ɳ��������ɳ������$n���£�$nԽ�������ݵþ�Խ�\n"+ NOR;
							break;
						case 2:
							msg += YELGRN"�����鸿����$n���µ����ر����һ����������$n���ζ�ס��\n"+ NOR;
							break;
						case 3:
							msg += YELGRN"����ʯ����������ͻȻ���¾�ʯ����$n��������֮�У�\n"+ NOR;
							break;
						case 4:
							msg += YELGRN"�������𡻣����µľ��������ˣ���$n���εĽ����ˣ�\n"+ NOR;
							break;
						case 5:
							msg += YELGRN"����Ԫ�ط籩�����񱩵���Ԫ�ؽ�$n������ΰ��أ�\n"+ NOR;
							break;
						case 6:
							msg += YELGRN"���������������ؿ�ʼ�𶯣��ŵ�$n���Ҷ�����\n"+NOR;
							break;
						case 7:
							msg += YELGRN"�����ν�硻����ص��������۳�һ��ԭ�εĽ�磬��$n�������ڣ�\n"+ NOR;
							break;
						case 8:
							msg += YELGRN"�����֮�ݡ������֮������֮ĸ���ʴȵĹ�â�£�$n���Ÿж����ģ�����Ĥ�ݣ�\n"+ NOR;
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
					msg += YELGRN"��ϵ����, ˭֪$n��װ���Զ�����һ����������ɵ�ס��$N�Ĺ�����\n"NOR;
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
					msg += YELGRN"��ϵ����, ˭֪$N�Ŀ���ʵ�ڲ����Ȼ�����ˣ�\n"NOR;
					message_vision(msg, me, victim);
				}
				break;
			case 5:
				wuxing_damage = calculate_wuxing_damage(me, victim, wuxing_damage, wuxing_type, op_rate);
				msg = HIM + msg_head+HIM"ʹ��";;
				if(wuxing_damage>0)
				{
					if( random(level) < 5 )
						msg += HIM"������Ԫ�ط籩�����񱩵�Ԫ�ؽ���$n�����壬����$n����˼�����˺���\n"+ NOR;
					else
						msg += HIM"������֮ŭ���� �񱩵�����������$n˺����Ƭ��\n"NOR;
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
					msg += HIM"���з���, ˭֪$n��װ���Զ�����һ����������ɵ�ס��$N�Ĺ�����\n"NOR;
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
					msg += HIM"���з���, ˭֪$N�Ŀ���ʵ�ڲ����Ȼ�����ˣ�\n"NOR;
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
			msg_head = "ֻ��$N���е�" + weapon->query("name");
		else {
			msg_head = "ֻ��$N��";
			switch(random(5)) {
				case 0:
				default:
					msg_head += "˫��";
					break;
				case 1:
					msg_head += "����";
					break;
				case 2:
					msg_head += "�ŵ�";
					break;
				case 3:
					msg_head += "��";
					break;
				case 4:
					msg_head += "����";
					break;
			}
		}
		switch(me->query_temp("newitem_wuxing_counter")) {
			case 0:
			default:
					wuxing_damage = calculate_wuxing_damage(me, victim, "gold");
					if (wuxing_damage>0) {
						msg = HIY + msg_head + HIY + "��$n�����������, $n�޴Ӷ���, �����ñ�������!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						victim->receive_damage("kee", wuxing_damage, me);
						victim->receive_wound("kee", wuxing_damage/2, me);
						message_vision(msg, me, victim);
						report_status(victim);
					} else  if (wuxing_damage == 0){
						msg = msg_head + "��$n�����������, ȴ��$n̸Ц���������ļ�϶������, ���ɱܿ�!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 1:
					wuxing_damage = calculate_wuxing_damage(me, victim, "wood");
					if (wuxing_damage>0) {
						msg = HIG + msg_head + HIG + "͵͵�ɳ�һ���ޱȾ޴����ľ, $nһ��û����, �����ص�������ͷ��, ��ʱ���ǲ���!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						victim->receive_damage("sen", wuxing_damage, me);
						victim->receive_wound("sen", wuxing_damage/2, me);
						message_vision(msg, me, victim);
						report_sen_status(victim);
					} else if (wuxing_damage == 0){
						msg = msg_head + "͵͵�ɳ�һ���ޱȾ޴����ľ, �类$n����, ��һб��, ��ľ���ص������˵���!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 2:
					wuxing_damage = calculate_wuxing_damage(me, victim, "water");
					if (wuxing_damage > 0) {
						msg = HIB + msg_head + HIB + "�ó�һ����Ө��ˮ����$n��ȥ, Ӳ������$n���������˼������������ظ�$N!\n"
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
						msg = msg_head + "�ó�һ����Ө��ˮ����$n��ȥ, ����$n����һЦ, ����һ��, ˮ������ɢ���ڵز�����״!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 3:
					wuxing_damage = calculate_wuxing_damage(me, victim, "fire");
					if (wuxing_damage>0) {
						msg = HIR + msg_head + HIR + "�ó�һȺ������$n��ȥ. $n��Ȼ�����˴�, ���Ǳ�������ȥ�����ڵ�. $N�ӹ������������ڵ�, һ��������ȥ!\n"
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
						msg = msg_head + "�ó�һȺ������$n��ȥ. ȷ��$n���������д�, �����������һ�����, ����Щ����ֻ��øɸɾ���!\n";
						message_vision(msg, me, victim);
					}
				break;
			case 4:
					wuxing_damage = calculate_wuxing_damage(me, victim, "earth");
					if (wuxing_damage>0) {
						msg = YELGRN + msg_head + YELGRN + "�������쳾����$n��ȥ, $nһʱû�з���, �����˿�����æ����!\n"
							  + NOR;
						if (wizardp(me)) {
							tell_object(me, "wuxing_damage = " + wuxing_damage + "\n");
						}
						if ( !victim->is_busy() )
							victim->start_busy( 1 + random( 2 ) );
						message_vision(msg, me, victim);
					} else  if (wuxing_damage == 0){
						msg = msg_head + "�������쳾����$n��ȥ, $nȴ�Ӷ�����, ����һ����, ��ѳ����ε�������ɽȥ��!\n";
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
    message_vision("$N��һ������������ɨ�����ڳ���ÿһ���ˡ�\n", me);

    if( (int)me->query("force") > (random(bellicosity) + bellicosity)/2 ) return;

    if( bellicosity > (int)me->query("score")
    &&  !wizardp(obj) ) {

        // auto kill, mark my_killer_list. -- mon 9/23/98
//      if(userp(me) && userp(obj)) {
//      set_my_killer_list(me, obj);
//      }

        message_vision("$N����$n�ȵ���" + RANK_D->query_self_rude(me)
        + "����ʵ�ںܲ�˳�ۣ�ȥ���ɡ�\n", me, obj);
me->set_temp("kill/target/"+obj->query("id"),1);
        me->kill_ob(obj);
    } else {
        message_vision("$N����$n�ȵ���ι��" + RANK_D->query_rude(obj)
            + "��" + RANK_D->query_self_rude(me) + "�������˴�ܣ����������ְɣ�\n",
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
                        message_vision("\n$N��ž����һ�����ڵ��ϣ������ų鶯�˼��¾����ˡ�\n\n", ob);
                        break;
         case "unconcious":
                        message_vision("\n$N��־�Ժ�������һ�����ȣ����ڵ��ϻ��˹�ȥ��\n\n", ob);
                        break;
                case "revive":
                         if(ob->query("blind") || ob->query("race") != "����")
			     message_vision("\n$N����һ����Ť���˼��£������˹�����\n\n", ob);
			else if(ob->query("mute"))
			     message_vision("\n$N���������˹����������۾�վ����ҡ��ҡͷ��\n\n", ob);
			else message_vision("\n$N���Ӷ��˶������������˼��������ѹ�����\n\n", ob);
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
			JJ_MANMADE_NPCD->announce_msg( "��[" + environment(killer)->query("short") + "] " + killer->query("name")
			      + "(" + killer->query("id") +") ɱ���� " + victim->query("name")
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
	   			case 0 : killmsg = "$o����������$t�����¡�" ;
	   				 break ;
	   			case 1 : killmsg = "$t�����޵У���$oն�����¡�";
	   				 break ;
	   			case 2 : killmsg = "�ҽ����У�$t�ѽ�$o�׼��������С�";
	   				 break ;
	   			default : killmsg = "һ���ҽУ�$o�Ѿ���$t��ȥ���졣";
	   		}
	   		rkmsg = victim->query("name")+"��"+victim->query("id")+"��" ;
	   		killmsg = replace_string ( killmsg, "$o", rkmsg );
	   		rkmsg = killer->query("name")+"��"+killer->query("id")+"��" ;
	   		killmsg = replace_string ( killmsg, "$t", rkmsg );
	   		if ((killer->query_temp("pkgame"))==(victim->query_temp("pkgame"))) killer->add_temp( "pgwin" , -1 );  // ��csϵͳ������
	   		if ((killer->query_temp("pkgame"))!=(victim->query_temp("pkgame"))) killer->add_temp( "pgwin" , 1 );   // ͬ��
	   		if (!victim->query_temp("pkgame") && userp(victim)) killer->die(); //ͬ��
	   		CHANNEL_D->do_channel ( this_object() , "rumor" , killmsg );
	   	}else if ( killer == victim )
	   	{
	   		CHANNEL_D->do_channel ( this_object() , "rumor" , "���ڣ��������ڼ���"HIW+victim->query("name")+HIM"��������ǿ��Ķ�����������ѹ�������������ڰ�ȫ����" );
	   		if ( killer->query_temp("pkgame") ) killer->add_temp( "pgwin" , -1 );
	   	}
	      	victim->clear_condition();
		victim->delete_temp("last_fainted_from");
		killer->remove_all_killer();
		victim->remove_all_killer();
		if ( killer != victim )
		message_vision(HIR"\n\n�ۼ�$N���У���$nһ���ߵ�CS��Ϣ��ȥ�ˡ�\n"NOR,victim,killer);
	        else if ( killer == victim )
	        message_vision(HIR"\n\n$N̫��С�ˣ�������ȥ��Ϣ�Ҵ����������ɡ�\n"NOR,victim);
	        if (victim->query_temp("pkgame")) victim->move("/u/take/waitpk");
	        oUser = users();
		for ( i = 0 ; i < sizeof(oUser) ; i ++ )
        	{
        		if ((oUser[i]->query_temp("pkgame")==victim->query_temp("pkgame")) && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR))
        			i = sizeof(oUser)+1;
                }
        	if ( i == sizeof(oUser) )
        	{
        		if ( killer == victim )
        		{
        			if ( (killer->query_temp("pkgame") == "t") && (sizeof(fire) == 0) )
        			{
        				message( "system", BLINK HIR"\n�� CS �������� ���ֽ������˾ֱ���"+HIY"����"+BLINK HIR"���ʤ,���λ׼��5���Ӻ�ʼ��һ�ֱ���������������\n" NOR, users() );
       					"/cmds/usr/pkgame"->over();
       					"/cmds/usr/pkgame"->query_Win("ct");
       				}
        			if ( killer->query_temp("pkgame") == "ct" )
        			{
       					message( "system", BLINK HIR"\n�� CS �������� ���ֽ������˾ֱ���"+HIY"�ݻ�"+BLINK HIR"���ʤ,���λ׼��5���Ӻ�ʼ��һ�ֱ���������������\n" NOR, users() );
       					"/cmds/usr/pkgame"->over();
       					"/cmds/usr/pkgame"->query_Win("t");
       				}
       			}
       			if ( killer != victim )
       			{
       				if ( killer->query_temp("pkgame") == "t")
        			{
       					message( "system", BLINK HIR"\n�� CS �������� ���ֽ������˾ֱ���"+HIY"�ݻ�"+BLINK HIR"���ʤ,���λ׼��5���Ӻ�ʼ��һ�ֱ���������������\n" NOR, users() );
       					"/cmds/usr/pkgame"->over();
       					"/cmds/usr/pkgame"->query_Win("t");
       				}
       				fire = children ("/d/dntg/sky/obj/fire");
       				if ( (killer->query_temp("pkgame") == "ct") && (sizeof(fire) == 0) )
        			{
        				message( "system", BLINK HIR"\n�� CS �������� ���ֽ������˾ֱ���"+HIY"����"+BLINK HIR"���ʤ,���λ׼��5���Ӻ�ʼ��һ�ֱ���������������\n" NOR, users() );
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
	 	{	rkmsg="ն";	}
		break;
		case "slice":
	 	{	rkmsg="��";	}
		break;
		case "chop":
	 	{	rkmsg="��";	}
		break;
		case "hack":
	 	{	rkmsg="��";	}
		break;
		case "thruse":
	 	{	rkmsg="��";	}
		break;
		case "pierce":
	 	{	rkmsg="��";	}
		break;
		case "wave":
	 	{	rkmsg="��";	}
		break;
		case "whip":
	 	{	rkmsg="��";	}
		break;
		case "impale":
	 	{	rkmsg="��";	}
		break;
		case "rake":
	 	{	rkmsg="��";	}
		break;
		case "bash":
	 	{	rkmsg="��";	}
		break;
		case "crush":
	 	{	rkmsg="��";	}
		break;
		case "slam":
	 	{	rkmsg="��";	}
		break;
		case "throw":
	 	{	rkmsg="��";	}
		break;
		case "shoot":
	 	{	rkmsg="��";	}
		break;
//now start cast :
//		case "cast_qiankun":	//�ǹ����� transfer , chuqiao, qiankun, yinshen
//		{	rkmsg="";	}
//		break;
		case "cast_zhenhuo":
		{	rkmsg="̫�����";		}
		break;
		case "cast_baxian":
		{	rkmsg="���ɴ���";		}
		break;
		case "cast_bighammer":
		{	rkmsg="������ħ��";		}
		break;
		case "cast_jingang":
		{	rkmsg="�ٻ����";		}
		break;
		case "cast_jinguzhou":
		{	rkmsg="������";		}
		break;
		case "cast_thunder":
		{	rkmsg="������";		}
		break;
		case "cast_invocation":
		{	rkmsg="�ٻ��콫";		}
		break;
		case "cast_fenshen":
		{	rkmsg="������";		}
		break;
		case "cast_dingshen":
		{	rkmsg="����";		}
		break;
		case "cast_light":
		{	rkmsg="�����";		}
		break;
		case "cast_jieti"://escape, tudun, suliao, huanying
		{	rkmsg="��ħ�����";		}
		break;
		case "cast_sanmei":
		{	rkmsg="��ζ���";		}
		break;
		case "cast_zhuang":
		{	rkmsg="ƽ���";		}
		break;
		case "cast_arrow":
		{	rkmsg="�������";		}
		break;
		case "cast_shiyue":// mihun huimeng
		{	rkmsg="ʴ����";		}
		break;
		case "cast_hufa":
		{	rkmsg="�ٻ�����";		}
		break;
		case "cast_freez":
		{	rkmsg="ѩ�����";		}
		break;
		case "cast_jiushen":
		{       rkmsg="����";       }
		break;
		case "cast_jianshen":
		{       rkmsg="����";       }
		break;
		case "cast_gouhun"://miwu
		{	rkmsg="������";		}
		break;
		case "cast_animate":
		{	rkmsg="������";		}
		break;
/*		case "cast_":
		{	rkmsg="";		}
		break;
*/
// now start perform msg
		case "perform_sanban":
		{	rkmsg="�޵����師";		}
		break;
		case "perform_qiangjian":
		{	rkmsg="ǹ����";		}
		break;
		case "perform_storm":
		{	rkmsg="��������";		}
		break;
		case "perform_diyu":
		{	rkmsg="�������";		}
		break;
		case "perform_pili":
		{	rkmsg="��������";		}
		break;
		case "perform_qiankun":
		{	rkmsg="Ǭ��һ��";		}
		break;
		case "perform_pozhan":
		{	rkmsg="�����ٳ�";		}
		break;
		case "perform_zhangxinlei":
		{	rkmsg="������";		}
		break;
		case "perform_flower":
		{	rkmsg="��Ůɢ��";	}
		break;
		case "perform_diezhang":
		{	rkmsg="����";		}
		break;
		case "perform_huifeng":
		{	rkmsg="���";		}
		break;
		case "perform_wuxue":
		{	rkmsg="��ѩ";		}
		break;
		case "perform_sheshen":
		{	rkmsg="����";		}
		break;
		case "perform_three":
		{	rkmsg="���ˡ���";	}
		break;
		case "perform_chaofeng":
		{	rkmsg="���񳯷�";	}
		break;
/*		case "perform_":
		{	rkmsg="";		}
		break;
*/

//now start exert .........// �ǹ����� recover refresh transfer regenerate heal lifeheal
		case "exert_sheqi":
		{	rkmsg="����";		}
		break;
		case "exert_roar":
		{	rkmsg="����";		}
		break;

		case "special_msg"://����Ĺ���
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
	     		str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"��"HIY+weapon->name()+HIM+rkmsg+"���ˡ�"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			} else {
			if(rkmsg && !weapon)
			{
			str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"��һ��"+HIW"��"+rkmsg+"��"+HIM"��ȥ����������"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			}else if(weapon && !rkmsg){
			str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"��"HIY+weapon->name()+HIM"��ȥ�˼���������"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
					   }else {
			str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"ɱ���ˡ�"+str;
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
						  }



	     	}
	     	if(!victim->query("tongji/fanren")&&vics&&member_array(victim->query("id"),vics)>-1)
	{

	  message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer->name(1)+"��������������������������"+victim->name(1)+"���������ٸ�ͨ����\n"+NOR,users());
	  killer->set("tongji/fanren",1);
	  killer->set("tongji/mudage",killer->query("mud_age"));
	  //added for prison
	  killer->add("tongji/pktime",1);
	  killer->delete_temp("kill/target/"+victim->query("id"));
	  str = "��˵"+killer->name(1)+"ɱ���ˣ�����������";
	  CHANNEL_D->do_channel(this_object(), "rumor",str);
	  if(killer->query("tongji/pktime")>=3)
            {
                  killer->move("/d/wiz/dalao");
          message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer->query("name")+"����ɱ���������ֱ��ؽ����Σ�������䣡\n"NOR,users());
            }
	}
	else if(victim->query("tongji/fanren"))
	{

	message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer->name(1)+"ɱ��ͨ����"+victim->name(1)+"�й�����ͨ���ν���\n"+NOR,users());
	killer->add("kill/pkgain",gain);
        killer->add("combat_exp",gain);
        killer->add("PKFANREN",1);
	victim->delete("tongji");
        str=chinese_daoxing(gain);
        if(strlen(str)<=1)
	str="���";
        str=killer->name(1)+"�õ���"+str+"���У�";
        str=victim->name(1)+"��"+killer->name(1)+
            "�͵�������"+str;
        CHANNEL_D->do_channel(this_object(), "rumor",str);

       }else if(kils&&member_array(killer->query("id"),kils)>-1)
       {

        str=victim->name(1)+"��"+killer->name(1)+
            "��������ɱ���ˡ�";
        CHANNEL_D->do_channel(this_object(), "rumor",str);
       }else {

	message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer->name(1)+"ʧ�ִ�����"+victim->name(1)+"��������������֪�������ߣ��ٱ�֪�ٸ���\n"+NOR,users());
	killer->set("tongji/fanren",1);
	killer->set("tongji/mudage",killer->query("mud_age"));
	killer->add("tongji/pktime",1);
	//added for prison
	killer->delete_temp("kill/target/"+victim->query("id"));
	str = "��˵"+killer->name(1)+"���ʧ���ˣ������ٸ�ͨ����";
	CHANNEL_D->do_channel(this_object(), "rumor",str);
if(killer->query("tongji/pktime")>=3)
 {
 killer->move("/d/wiz/dalao");
  message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer
->query("name")+"����ɱ���������ֱ��ؽ����Σ�������䣡\n"NOR,users());
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
//		  sprintf("%s��%sɱ���ˡ�", victim->name(1), killer->name(1)));
/////////////////for NK rumor

			weapon=killer->query_temp("kill_weapon");
			if(weapon && rkmsg)
			{
	     		str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"��"HIY+weapon->name()+HIM+rkmsg+"���ˡ�";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			} else {
			if(rkmsg && !weapon)
			{
			str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"��һ��"+HIW"��"+rkmsg+"��"+HIM"��ȥ�����޵ظ���";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
			}else if(weapon && !rkmsg){
			str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"��"HIY+weapon->name()+HIM"��ȥ�����޵ظ���";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
					   }else {
			str=victim->name(1)+"��"+
	         	MISC_D->find_place(environment(killer))+"��"+killer->name(1)+"ɱ���ˡ�";
	     		CHANNEL_D->do_channel(this_object(), "rumor",str);
						  }
    if(userp(killer))
{
           if(!victim->query("tongji/fanren")&&vics&&member_array(victim->query("id"),vics)>-1)
	{
	  message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer->name(1)+"��������������������������"+victim->name(1)+"���������ٸ�ͨ����\n"+NOR,users());
	  killer->set("tongji/fanren",1);
	  killer->set("tongji/mudage",killer->query("mud_age"));
	  //added for prison
	  killer->add("tongji/pktime",1);
	  killer->delete_temp("kill/target/"+victim->query("id"));
	  str = "��˵"+killer->name(1)+"ɱ���ˣ�����������";
	  CHANNEL_D->do_channel(this_object(), "rumor",str);
if(killer->query("tongji/pktime")>=3)
 {
 killer->move("/d/wiz/dalao");
  message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer
->query("name")+"����ɱ���������ֱ��ؽ����Σ�������䣡\n"NOR,users());
            }

	}
	else if(victim->query("tongji/fanren"))
	{
	message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer->name(1)+"ɱ��ͨ����"+victim->name(1)+"�й�����ͨ���ν���\n"+NOR,users());
	killer->add("kill/pkgain",gain);
        killer->add("combat_exp",gain);
        killer->add("PKFANREN",1);
	victim->delete("tongji");
        str=chinese_daoxing(gain);
        if(strlen(str)<=1)
	str="���";
        str=killer->name(1)+"�õ���"+str+"���У�";
        str=victim->name(1)+"��"+killer->name(1)+
            "�͵�������"+str;
        CHANNEL_D->do_channel(this_object(), "rumor",str);

       }else if(kils&&member_array(killer->query("id"),kils)>-1)
       {

        str=victim->name(1)+"��"+killer->name(1)+
            "��������ɱ���ˡ�";
        CHANNEL_D->do_channel(this_object(), "rumor",str);
       }else {

	message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer->name(1)+"ʧ�ִ�����"+victim->name(1)+"��������������֪�������ߣ��ٱ�֪�ٸ���\n"+NOR,users());
	killer->set("tongji/fanren",1);
	killer->set("tongji/mudage",killer->query("mud_age"));
	killer->add("tongji/pktime",1);
	//added for prison
	killer->delete_temp("kill/target/"+victim->query("id"));
	str = "��˵"+killer->name(1)+"���ʧ���ˣ������ٸ�ͨ����";
	CHANNEL_D->do_channel(this_object(), "rumor",str);
if(killer->query("tongji/pktime")>=3)
 {
 killer->move("/d/wiz/dalao");
  message("channel:xyj",HIR+"������ͨ�桿Ѧ�ʹ�(xueren gui)��"+killer
->query("name")+"����ɱ���������ֱ��ؽ����Σ�������䣡\n"NOR,users());
            }

	  	}
        }
      if(!userp(killer)&&userp(victim)&&victim->query("tongji/fanren"))
   {
          str=victim->name(1)+"��"+killer->name(1)+
            "�͵�������";
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
                		CHANNEL_D->do_channel(victim, "rumor",killer->name() + "ɱ����"
                		     + victim->query("family/family_name") + victim->name()
                   		     + "(" + victim->rzr_get_my_level() + "��), �����õ��޿�ͳ���װ����, ���õ���"
                   		     + pot_gain + "��Ǳ��");
			  	  } else {
					  CHANNEL_D->do_channel(victim, "rumor",killer->name() + "ɱ����"
					      + victim->query("family/family_name") + victim->name()
					      + "(" + victim->rzr_get_my_level() + "��), �����õ��޿�ͳ���װ����, �����ڵĶ��黹�õ���"
                   		  + ( pot_gain + pot_gain / 10 ) + "��Ǳ��");
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
                // tell_object(killer,"\n��õ���"+str+"���С�\n");
                // tell_object(killer,"\n��õ���"+exp_gain+"���С�\n");
          		killer->add("potential",pot_gain);
              	if (victim->is_manmade_npc())
			tell_object(killer,"\n��õ���"+pot_gain+"Ǳ�ܡ�\n");
		  		msg=sprintf("%s(%s)ɱ����%s(%s)���õ�%d�����,%d��Ǳ�ܺ�%d�����С�",
		  		killer->query("name"), killer->query("id"),
		    	victim->query("name"), victim->query("id"),reward,pot_gain,exp_gain);
			} else {
				object killer_env;
				int team_total;
				int exp_share, dist_exp;
				int daoxing_share, dist_daoxing;
				int pot_share, dist_pot;
				msg = "����ɱ���� " + victim->query("family/family_name") + victim->query("name") +
				      "(" + victim->rzr_get_my_level() + "��), �ڳ��Ķ�Ա:\n";
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
						      + ")�õ���" + chinese_daoxing(daoxing_share) + "����, "
						      + pot_share + "��Ǳ��, " + exp_share + "����\n";
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
				msg += "���һ���� - " + killer->query("name") + "(" + killer->query("id") +
				       ")�õ���" + chinese_daoxing(daoxing_share) + "����, "
						      + pot_share + "��Ǳ��, " + exp_share + "����\n";
				msg += "����������: " + chinese_daoxing(reward) + "����, "
						      + pot_gain + "��Ǳ��, " + exp_gain + "����\n";
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
             if(year) str=str+chinese_number(year)+"��";
             if(day) str=str+chinese_number(day)+"��";
             if(hour) str=str+chinese_number(hour)+"ʱ��";

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
                HIC "$N����ָͷѸ������ͻȻ����һ�磡��Ȼ��������������һ����$n��ȥ��\n" NOR,
                        //initial message
                HIC "���$n���յý�ͷ�ö\n" NOR,
                        //success message
                HIC "����$n����һ���Ͷ��˿�����\n" NOR,
                        //fail message
                HIC "���ǻ��汻$n�Է���һ�ƣ�����$N�ؾ��ȥ��\n" NOR,
                        //backfire initial message
                HIC "���̫������ɣ�$n���յý�ͷ�ö\n" NOR
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
        message_vision(HIB "������ñ�$N��������ס��˭Ҳû�гԿ���\n" NOR, target);

        //let the target kill attacker.
        target->kill_ob(attacker);

        return;
}

int do_attack_damage(object me, object victim, object weapon)//�����˺������൱��ֱ�Ӵ��е��ˣ�����һ�����ܵ��˺�
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
