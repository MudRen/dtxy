// taiji-quan.c ̫��ȭ
#include <ansi.h>
inherit SKILL;
#include "/daemon/skill/eff_msg.h";
int taiji(object me, object victim);

mapping *action = ({
([  "action" : "$N��̫��������ʽ����˫���´����ֱ����⣬��������������������ǰ",
    "force" : 65,
    "dodge" : 25,
    "lvl" : 0,
    "skill_name" : "����ʽ",
    "damage_type" : "����"
]),
([  "action" : "$N����һ�С���ȸβ����˫�ֻ��˸���Ȧ����������������$n��$l",
    "force" : 95,
    "dodge" : 15,
    "lvl" : 5,
    "skill_name" : "��ȸβ",
    "damage_type" : "����"
]),
([  "action" : "$N���$n��һ�С����ޡ���������ȭ�������ϻ�����һǰһ�����ƽ��",
    "force" : 105,
    "dodge" : 15,
    "lvl" : 10,
    "skill_name" : "����",
    "damage_type" : "����"
]),
([  "action" : "$N���С��������ơ�������������������ǰ����۰뻷���ұ�ֱ�죬����$n��$l",
    "force" : 125,
    "dodge" : 10,
    "lvl" : 15,
    "skill_name" : "��������",
    "damage_type" : "ץ��"
]),
([  "action" : "$N���Ŷ����������鰴������ʹһ�С��׺����᡹����ȭ��ץ��$n��$l��ȥ",
    "force" : 95,
    "dodge" : 10,
    "lvl" : 20,
    "skill_name" : "�׺�����",
    "damage_type" : "ץ��"
]),
([  "action" : "$N����΢�����鲽��һ�ǡ�§ϥ��������������ǰ�����»�������$n$l��",
    "force" : 100,
    "dodge" : 15,
    "lvl" : 25,
    "skill_name" : "§ϥ����",
    "damage_type" : "����"
]),
([  "action" : "$N�ұ۰뻷������������һ�С��ֻ����á���ʮָ���ţ���������$n��$l",
    "force" : 115,
    "dodge" : 10,
    "lvl" : 30,
    "skill_name" : "�ֻ�����",
    "damage_type" : "ץ��"
]),
([  "action" : "$N������ֱ�������黮�������ұ��������һ�ǡ�����������������$n��$l",
    "force" : 135,
    "dodge" : 3,
    "lvl" : 35,
    "skill_name" : "����������",
    "damage_type" : "����"
]),
([  "action" : "$N�����������������黮���������»�����ȭ��һ�ǡ�ָ�ɴ�������$n���ɲ�",
    "force" : 190,
    "dodge" : 15,
    "lvl" : 40,
    "skill_name" : "ָ�ɴ�",
    "damage_type" : "����"
]),
([  "action" : "$N˫���»���ȭ�������ǰ������Ȧ��һ�С�˫�������������������$n��̫��Ѩ",
    "force" : 150,
    "dodge" : 10,
    "lvl" : 45,
    "skill_name" : "˫����",
    "damage_type" : "����"
]),
([  "action" : "$N�󲽳��飬���������鰴�����ֳ�����ʹһ�С��������š�����$n��$l��ȥ",
    "force" : 135,
    "dodge" : 15,
    "lvl" : 50,
    "skill_name" : "��������",
    "damage_type" : "ץ��"
]),
([  "action" : "$N������ȸβ�����ҽ�ʵ������飬�����־���ճ��ճ�棬��ס$n���ᾢ����",
    "force" : 125,
    "dodge" : 10,
    "lvl" : 55,
    "skill_name" : "��ȸβ",
    "damage_type" : "����"
]),
([  "action" : "$N�ҽ����������ֻ�Ȧ�󸧣�һ�С���̽��������Բת��ǰ����$n���Ż�ȥ",
    "force" : 110,
    "dodge" : 5,
    "lvl" : 60,
    "skill_name" : "��̽��",
    "damage_type" : "����"
]),
([  "action" : "$Nʩ��������ʽ�����������⻮��ס$n��������������ָ������$n��$l",
    "force" : 125,
    "dodge" : 10,
    "lvl" : 65,
    "skill_name" : "����ʽ",
    "damage_type" : "����"
]),
([  "action" : "$N���ֱ��ƺ�����ǰ��������ȭ�����´�����һ�С���׿�����������$n��$l",
    "force" : 110,
    "dodge" : 9,
    "skill_name" : "��׿���",
    "lvl" : 70,
    "damage_type" : "����"
]),
([  "action" : "$N���ǰ̤�벽����������ʹһ�С������롹����ָ�������ϴ���$n���ɲ�",
    "force" : 130,
    "dodge" : 13,
    "skill_name" : "������",
    "lvl" : 75,
    "damage_type" : "ץ��"
]),
([  "action" : "$Nһ�С���ͨ�ۡ������һ������������$n��ǰ�������Ͼ���Ʋ������̫����������$n", 
    "force" : 210,
    "dodge" : 14,
    "skill_name" : "��ͨ��",
    "lvl" : 80,
    "damage_type" : "����"
]),
([  "action" : "$N�ҽ�̤������������ȭ�黮�����ƻ��б��£���ǡ������ơ�һ�����㽫$n����̫��Ȧ��",
    "force" : 180,
    "dodge" : 5,
    "lvl" : 85,
    "skill_name" : "������",
    "damage_type" : "����"
]),
([  "action" : "$N�����������ȡ��ɿ衢��������ϥ������������һ�С�������������$n��$l",
    "force" : 160,
    "dodge" : 11,
    "skill_name" : "����",
    "lvl" : 90,
    "damage_type" : "����"
]),
([  "action" : "$N���������ҽŶ�����ʹһ�С��𼦶�������˫ȭ����������̫��ȦȦ��$n��$l",
    "force" : 140,
    "dodge" : 14,
    "skill_name" : "�𼦶���",
    "lvl" : 95,
    "damage_type" : "����"
]),
([  "action" : "$N������̤��˫����ȭ�����ӳ���ʹһʽ����Ů���󡹣�˳��$n�ֱ�ֱ�ϣ�����$nǰ��",
    "force" : 200,
    "dodge" : 8,
    "skill_name" : "��Ů����",
    "lvl" : 100,
    "damage_type" : "����"
]),
([  "action" : "$N���ֻ�Ȧ�����־���ǰ��������ǰƲ����ʹһ�С�����Ʋ��������$n��$l��ȥ",
    "force" : 130,
    "dodge" : 11,
    "skill_name" : "����Ʋ��",
    "lvl" : 105,
    "damage_type" : "����"
]),
([  "action" : "$N�����鰴�����ֱ���������黮һ�С�ת����ȡ��������������$n��$l",
    "force" : 140,
    "dodge" : 11,
    "skill_name" : "ת�����",
    "lvl" : 110,
    "damage_type" : "����"
]),
([  "action" : "$N����һ�С��Դ��������ֻ�̫��Ȧ§��ϥ��������ȭ���»���������$n��$l",
    "force" : 140,
    "dodge" : 4,
    "skill_name" : "�Դ�",
    "lvl" : 115,
    "damage_type" : "����"
]),
([  "action" : "$N��̤���Ƿ�λ�������ң�˫ȭ�����ʮ�֣�һ�С��������ǡ�����$n��$l��ȥ",
    "force" : 230,
    "dodge" : 5,
    "skill_name" : "��������",
    "lvl" : 120,
    "damage_type" : "����"
]),
([  "action" : "$N����΢ת��������ֱ���ұ�΢����������ϣ�ʹһ�С�����������$n���ֱ˦��ȥ",
    "force" : 150,
    "dodge" : 10,
    "skill_name" : "�����",
    "lvl" : 125,
    "damage_type" : "����"
]),
([  "action" : "$N˫���쿪������������һ����Բ����һ�С�ת�����������$n������������������̫��Ȧ��",
    "force" : 170,
    "dodge" : 7,
    "skill_name" : "ת�����",
    "lvl" : 130,
    "damage_type" : "����"
]),
([  "action" : "$N���ֻ������գ�������ȭ��ǰ�Ƴ���ȭ�������һ�С��乭�仢����ֱ��$n$l��ȥ",
    "force" : 120,
    "dodge" : 11,
    "skill_name" : "�乭�仢",
    "lvl" : 135,
    "damage_type" : "����"
]),
([  "action" : "$Nʹ��һ�С����֡������ָߣ����ֵͣ�һ��ԲȦ�ѽ�$n$l��ס��̫���ᾢ�漴����",
    "force" : 300,
    "dodge" : 15,
    "lvl" : 140,
    "skill_name" : "����",
    "damage_type" : "����"

]),
([  "action" : "$N����һ�������Ծ����˫�ֻ�̫��Ȧ����$n�Ĺ�������������ץ��$n������������",
    "force" : 140,
    "dodge" : 10,
    "lvl" : 145,
    "skill_name" : "���Ծ",
    "damage_type" : "����"
]),
([  "action" : "����$Nһ�С�б���ơ�����$n������ƫ��˫ȭ�ڻ������������ɾ���һ������$n",
    "force" : 170,
    "dodge" : 25,
    "lvl" : 150,
    "skill_name" : "б����",
    "damage_type" : "����"
]),
([  "action" : "����$N���С�������ɽ����˫ȭ����������бת����$n���һ�ƣ���������Ҫ��$n�Ƴ�",
    "force" : 160,
    "dodge" : 15,
    "lvl" : 155,
    "skill_name" : "������ɽ",
    "damage_type" : "����"
]),
([  "action" : "$N������Ұ����ס���ת��$n�����ǰ�������ƽ����$n����һ�����뽫�����",
    "force" : 270,
    "dodge" : 17,
    "lvl" : 160,
    "skill_name" : "Ұ�����",
    "damage_type" : "����"
]),
([  "action" : "$Nʩ������ת�����������������ת����ȭ�����������ȭ����$n��$l",
    "force" : 180,
    "dodge" : 18,
    "lvl" : 165,
    "skill_name" : "��ת�������",
    "damage_type" : "����"
]),
([  "action" : "$N�����ֱ��������ƣ����ֽ��棬�̶����ҷֿ����ɰ��С�����Ʊա�����$n$l",
    "force" : 205,
    "dodge" : 10,
    "lvl" : 170,
    "skill_name" : "����Ʊ�",
    "damage_type" : "����"
]),
([  "action" : "$Nʩ����ת�����������������ת����ȭ�������Ͼ�����ڲ����$n��$l",
    "force" : 190,
    "dodge" : 15,
    "lvl" : 175,
    "skill_name" : "ת�������",
    "damage_type" : "����"
]),
([  "action" : "$Nʩ������ת�������������������ת����ϥ��������ȭ������ȭ��ǰ���$n",
    "force" : 200,
    "dodge" : 5,
    "lvl" : 180,
    "skill_name" : "��ת�������",
    "damage_type" : "����"
]),
([  "action" : "$N���ֱ�������������ǰ�������������������ϣ���������Ʊա���ǰ��������$n",
    "force" : 185,
    "dodge" : 17,
    "lvl" : 185,
    "skill_name" : "����Ʊ�",
    "damage_type" : "����"
]),
([  "action" : "$N����΢��ת����ϥ���裬���С�ʮ���֡�����ֻ�ֱ�΢�������ֱ��������໮������",
    "force" : 140,
    "dodge" : 7,
    "lvl" : 190,
    "skill_name" : "ʮ����",
    "damage_type" : "����"
]),
([  "action" : "$N����΢��ת�����С�ʮ���֡�����������������������ǰ�����ϱ����أ�������ʮ����",
    "force" : 120,
    "dodge" : 3,
    "lvl" : 195,
    "skill_name" : "ʮ����",
    "damage_type" : "����"
]),
([  "action" : "$N��ǰ������ǰ�죬���ҷֿ�����΢���������ƽ��������������������$n$l",
    "force" : 60,
    "dodge" : 25,
    "lvl" : 199,
    "skill_name" : "����",
    "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
    mapping fam  = me->query("family");
//    if (fam["family_name"] != "�䵱��" || fam["generation"] != 2)
//         return notify_fail("̫��ȭֻ�ܴ������ᴦѧ����\n");
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("��̫��ȭ������֡�\n");
//    if ((int)me->query_skill("yinyun-ziqi", 1) < 100)
//        return notify_fail("�����������򲻹����޷�ѧ̫��ȭ��\n");
    if ((int)me->query("max_force") < 500)
        return notify_fail("�������̫�����޷���̫��ȭ��\n");
//    if(me->query("taiji_quest") > me->query("taiji_zsf"))
//        return notify_fail("����ö�̫��ȭ��������⣬�޷�������ϰ̫��ȭ��\n");
    return 1;
}

string query_skill_name(int level)
{
    int i;
        for(i = sizeof(action)-1; i >= 0; i--)
               if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];    
}
void skill_improved(object me)
{
   int skill = me->query_skill("taiji-quan", 1);
   if(skill == 50 && !me->query("taiji_quest")) me->set("taiji_quest", 1);
   if(skill == 80 && me->query("taiji_zsf") < 2) me->set("taiji_quest", 2);
   if(skill == 110 && me->query("taiji_zsf") < 3) me->set("taiji_quest", 3);
   if(skill == 140 && me->query("taiji_zsf") < 4) me->set("taiji_quest", 4);
   if(skill == 170 && me->query("taiji_zsf") < 5) me->set("taiji_quest", 5);
   if(skill == 200 && me->query("taiji_zsf") < 6) me->set("taiji_quest", 6);   
   me->add("shen", me->query("combat_exp")/30);
}
mapping query_action(object me, object weapon)
{
    int i, j, level;
    object target; 
    level = (int) me->query_skill("taiji-quan",1);

    if (random(me->query_con()) > 30  &&  level > 120 && me->query("force") > 500){   
           me->add("force", -30);    
              return ([
                "action": HIY"$N����������������Ŀ������$n��������$p������£������������ɽ��ȴ����������"NOR,
                "force" : 150,
                "dodge" : 10,
                "damage" : 50,
                "damage_type" : "����",
                "post_action": (: taiji :)             
                ]); 
        }         
     for(i = sizeof(action); i > 0; i--) {
         if(level > action[i-1]["lvl"]) {
//            j = NewRandom(i, 20, level/5);
//            target = offensive_target(me);   
            if (me->query_temp("taiji")) {                
                    return ([  
                    "action" : action[j]["action"],
                    "force" : 100+action[j]["force"]*2,
                    "dodge":action[j]["dodge"]*3,
                    "lvl" : action[j]["lvl"],
                    "damage_type" : action[j]["damage_type"],
                    ]);
               }
            return action[j];
            }
         }
}

int practice_skill(object me)
{
    int lvl = me->query_skill("taiji-quan", 1);
    int i = sizeof(action);
    while (i--) if (lvl == action[i]["lvl"]) return 0;
    if ((int)me->query("sen") < 40)
        return notify_fail("�������̫���ˡ�\n");
    if ((int)me->query("force") < 20)
        return notify_fail("�������������̫��ȭ��\n");
    me->receive_damage("sen", 30);
//    if(me->query_skill("juehu-shou", 1))
//      me->add("neili", -(me->query_skill("juehu-shou", 1)/5));
         me->add("force", -20);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"taiji-quan/" + action;
}

int taiji(object me, object victim)
{
     string msg;
        if( random(me->query_kar()) > victim->query_kar()/20
           && !victim->is_busy()
           && me->query_skill_mapped("parry") == "taiji-quan") {
             msg = "$pֻ�����̸�·��ȫ����$P˫�Ƶ�����֮�£��޿����ܣ��޿ɵ�����ֻ���˾��ڱ���Ӳ������һ�ƣ�
ͬʱ�ұ۽��ӣ�ֻ�����˸���һ�У��ɸ����ܾ���֮�֡�\n";
             if(random(20) >= 18 && me->query("force") > 600){
                   msg += HIR"����$N˫��һȦ���籧̫����һ���ۻ��ޱȵ����������һ�����У�ֻ����$p��ԭ�ؼ�ת�߰��£�
��ת���ݣ������Ĵ���������ʹ����ǧ��׹��֮����ס���Σ�ȴ�������͵�ͨ�죬�Ǳ���״��\n"NOR;
//                   victim->receive_damage("sen", me->query_skill("taiji-quan", 1)*2);
//                   victim->start_busy(2+random(2));
                   me->add("force", -20);
                   }
             else msg += "$N������Ϣ΢�ϣ�����һ�С�б���ơ�����$N������ƫ���Լ�Ҳ�˿�������\n";
             message_vision(msg, me, victim);
             return 1;
        }
        return 1;
}

int ob_hit(object ob, object me, int damage)
{
        object wp1;
        string msg;
        int p,j,skill, neili, neili1;
        wp1 = ob->query_temp("weapon");
        skill = me->query_skill("taiji-quan", 1);
        neili = me->query("force");
        neili1 = ob->query("force");

      if(me->query_temp("fanzhen")){
      	 me->delete_temp("fanzhen");
         return 1;
        }
        msg = "$N˫��������̫��ԲȦ��$n��"+wp1->name()+"��һ�ƣ�";
      if(me->query("combat_exp") > ob->query("combat_exp")/2
         && me->query_skill_mapped("parry") == "taiji-quan"
//         && me->query_skill("yinyun-ziqi", 1) > 50
         && neili > 100 
         && skill > 50 
         && living(me)
//         && me->query_temp("taiji")
         && !ob->query("env/invisibility")
         && random(10) >= 1)
         {         
         if(random(10) < 15) me->set_temp("fanzhen", 1);   
         if(wp1) msg = "$N˫��������̫��ԲȦ��$n��"+wp1->name()+"��һ�ƣ�";
         else msg = "$N˫�ֻ������������̫��ԲȦ��";
         if(neili >= neili1/100 + damage/100){
              msg += "���$n��������̫��ȭ������������������\n",              
              ob->receive_damage("kee", damage/2+ob->query("force_factor")*2, me);
              ob->receive_wound("kee", ob->query("force_factor"), me);
              p = ob->query("kee")*100/ob->query("max_kee");
              msg += damage_msg(damage/2, "����");
              msg += "( $n"+eff_status_msg(p)+" )\n";
              j = -8000;
              }             
           else if(neili >= neili1/200+random(neili1/200)+random(damage/200)){
            msg += "���$n��������̫��ȭ��������ж��һ�ԣ�\n", 
              j = -8000;
              }
           else if(neili > neili1/200+damage/200){
              msg += "���$n��������̫��ȭ��������ж����һ���֣�\n", 
              j = -(damage/3+random(damage));               
              }
           else{
              msg += "���$n��������̫��ȭ��������ж����һС�룡\n", 
              j = -damage/3; 
              }           
           message_vision(msg, me, ob);
           return j;
       }          
}


