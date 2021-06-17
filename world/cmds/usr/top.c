#include <ansi.h>
#include <mudlib.h>
#include <zhuanshi.h>

inherit F_CLEAN_UP;
int top_list(object ob1,object ob2);
int get_score(object ob);
int main(object me, string arg)
{
    
    object *list,*ob;
    int i;
    string msg;
    object obj;
    
    seteuid(getuid(me));
        if(arg) {
        if(arg=="me") obj = me;
        else if (wizardp(me)) { obj = present(arg, environment(me));
             if (!obj) obj = find_player(arg);
             if (!obj) obj = find_living(arg);
        if (!obj) return notify_fail("��Ҫ�쿴˭��״̬��\n");
        } 
		else return notify_fail("ֻ����ʦ�ſ��Բ쿴���˵�״̬��\n");
         write("����ۺ����ۣ�" +get_score(obj)+"\n");
         return 1;}
         
         else{
      //ob = filter_array(objects(), (: userp($1) && !wizardp($1) && !$1->query("env/no_top") :));
      ob = filter_array(objects(), (: userp($1) && !wizardp($1) :));
    list = sort_array(ob, (: top_list :));
    msg =  "\n            �� "+BCYN HIW+CHINESE_MUD_NAME+"���߸������а�"NOR" ��\n";
    msg += "���������ө��ߩ����������������ө����������ߩө�����������\n";
    msg += "�� ���� ��    ��        ��    �� ��     ��  ���ۺ�  ���۩�\n";
    msg += "�ĩ������ة��������������������ة������������ة�����������\n";
      for (i = 0 ;i < 20 ; i++) {
if( i >= sizeof(list)) 
    msg += "����ʱ��ȱ��������������    ��������������������������   ��\n";
        else {
            if( !list[i] ) continue;
            if( !list[i]->query("id") ) continue;
            if(list[i] == me) msg += BBLU HIY;
            msg += sprintf("��  %-5s %-22s%-14s %6d   ��\n"NOR,chinese_number(i+1),list[i]->query("name")+"("+
            list[i]->query("id")+")",
            list[i]->query("family")?list[i]->query("family/family_name"):"��ͨ����",
            get_score(list[i]));
        }
    }
    msg += "����������������������������������������������������������\n";
// msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
write(HIR"����"HIG"ʢ��"NOR + NATURE_D->game_time() + "�ǡ�\n");
    write(msg);
    return 1;
   }
}
int top_list(object ob1, object ob2)
{
    int score1,score2;

    score1 = get_score(ob1);
    score2 = get_score(ob2);

    return score2 - score1;
}

int get_score(object ob)
{
    int tlvl,i,score,number;
    string *ski;
    mapping skills;

    reset_eval_cost();
    skills = ob->query_skills();
    number=sizeof(skills);
    if (!number) return 1; 
    ski  = keys(skills);
    for(i = 0; i<number; i++) {
        tlvl += skills[ski[i]];
    }  // count total skill levels
     score = tlvl/number;
    score += ob->query("max_force")/10;
    score += ob->query("max_mana")/10;
    score += ob->query_str() + ob->query_int() + ob->query_spi() + ob->query_con();
    score += (int)(ob->query("combat_exp")+zs_getSpentExp(ob->query("lunhui_zhuanshi")))/2500;
    score += (int)(ob->query("daoxing")+zs_getSpentDx(ob->query("lunhui_zhuanshi")))/2500;

    return score;
}

int help(object me)
{
write(@HELP
ָ���ʽ : top 
 
���ָ���������֪������ʮ���������Щ����ȥ�����ǡ� 
top me �鿴�Լ����ۺ����ۡ�
HELP
    );
    return 1;
}
 



