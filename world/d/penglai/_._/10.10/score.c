// created by vikee
// 2000.10
// score.c

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string display_attr(int gift, int value);
string status_color(int current, int max);
string date_string(int date);
string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob;
        mapping my;
        string line, str, skill_type, *marks;
        object weapon;
        int i, attack_points, dodge_points, parry_points;

        seteuid(getuid(me));
        if(!arg)
                ob = me;
        else if (wizardp(me)) {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("��Ҫ�쿴˭��״̬��\n");
        } else
                return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");

        my = ob->query_entire_dbase();

        line = sprintf( BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(ob), ob->short(1) );

        str = "";
        if( mapp(my["family"]) ) {
                if( my["family"]["master_name"] ) str = my["family"]["master_name"];
        }
        if( mapp(my["marks"]) ) {
                marks = keys( my["marks"] );
                for( i = 0; i < sizeof(marks); i ++ ) {
                        if( str != "" ) str += "��";
                        str += marks[i];
                }
        }

        line += sprintf( " "HIY"�ԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡ�"NOR"\n\n");
        line += sprintf( " ������[%s% 6s%s]  �Ա�[%s% 6s%s] ���䣺[%s% 6s%s]"NOR"\n",
                BBLU HIC, ob->query("name"), NOR,
                BBLU HIC, ob->query("gender"), NOR,
                BBLU HIG, chinese_number(ob->query("age")), NOR );
                
        line += sprintf( " ���ࣺ[%s% 6s%s]  ��ϵ��[%s%-42s%s]\n",
                BBLU HIC, ob->query("race"), NOR,
                BBLU HIC, ob->query("title"), NOR );
                                
        if( str != "" ) line += sprintf( " ʦ�У�[%s% 6s%s]  ���գ�[%s%-42s%s] \n",BBLU HIC, str, NOR,
                                BBLU HIY,  CHINESE_D->chinese_date(((int)ob->query("birthday") - 14*365*24*60) * 60) , NOR );

        if( objectp(weapon = ob->query_temp("weapon")) )
                skill_type = weapon->query("skill_type");
        else
                skill_type = "unarmed";

        attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
        parry_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_DEFENSE);
        dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

        line += sprintf( " ��ò  [%s %4s %s]  ",
                BBLU, display_attr(my["per"], ob->query_per()), NOR );
        line += "����  " + tribar_graph(my["sen"], my["eff_sen"], my["max_sen"], BMAG, HIW ,HIR)
                + sprintf( "  [%s%8d%s / %s%7d%s]\n", BBLU HIW, my["sen"], HIG,
                HIM, my["max_sen"],  NOR );

        line += sprintf( " ��Ե��[%s %4d %s]  ",
                BBLU HIY, ob->query("kar"), NOR );
                                
        line += "��Ѫ  " + tribar_graph(my["kee"], my["eff_kee"], my["max_kee"], BMAG, HIW ,HIR)
                + sprintf( "  [%s%8d%s / %s%7d%s]\n", BBLU HIW, me->query("kee"), HIG,
                HIM, my["max_kee"],NOR );

        line += sprintf( " ���ԣ�[%s %4s %s]  ",
                BBLU, display_attr(my["str"], ob->query_int()), NOR );
        
                line += "������" + tribar_graph(my["force"], ob->query("force"),
                ob->query("max_force"), BBLU, HIC ,HIR)
                + sprintf( "  [%s%8d%s / %s%7d%s]\n", BBLU HIC, my["force"], HIG,
                HIC, ob->query("max_force"),NOR );


        line += sprintf( " ���[%s %4s %s]  ",
                BBLU, display_attr(my["str"], ob->query_str()), NOR );
        
        line += "������" + tribar_graph(my["mana"], ob->query("mana"),
                ob->query("max_mana"), BBLU, HIC ,HIR)
                + sprintf( "  [%s%8d%s / %s%7d%s]\n", BBLU HIC, my["mana"], HIG,
                HIC, ob->query("max_mana") ,NOR );
        
        
                line += sprintf( " ���ǣ�[%s %4s %s]  ",
                BBLU, display_attr(my["str"], ob->query_con()), NOR );
                                
                if( my["food"] * 100 / ob->max_food_capacity() > 10 ) str = HIC + "����";
        else str = HIR + "ȱʳ";

        line += "ʳ�" + tribar_graph(my["food"], ob->max_food_capacity(),
                ob->max_food_capacity(), BBLU, HIC ,HIR)
                + sprintf( "  [%s%4d%s / %s%4d%s , %4s%s]\n", BBLU HIC, my["food"], HIG,
                HIC, ob->max_food_capacity(), HIG, str, NOR );    
     

        
                line += sprintf( " ���ԣ�[%s %4s %s]  ",
                BBLU, display_attr(my["str"], ob->query_spi()), NOR );
        
        if( my["water"] * 100 / ob->max_water_capacity() > 10 ) str = HIC + "����";
        else str = HIR + "ȱˮ";

        line += "��ˮ��" + tribar_graph(my["water"], ob->max_water_capacity(),
                ob->max_water_capacity(), BBLU, HIC ,HIR)
                + sprintf( "  [%s%4d%s / %s%4d%s , %4s%s]\n", BBLU HIC, my["water"], HIG,
                HIC, ob->max_water_capacity(), HIG,  str, NOR );                
        
                line += sprintf( " ��ʶ��[%s %4s %s]  ",
                BBLU, display_attr(my["cor"], ob->query_spi()), NOR );
        
        
                line += sprintf("������[%s%12d%s (%s+%4d%s)%s]  ������[%s%12d%s]%s\n" NOR,
                BBLU HIC, attack_points + 1, HIG, HIW, ob->query_temp("apply/damage"), HIG, NOR,
                BBLU HIC, dodge_points + 1, NOR, NOR);


                line += sprintf( " ������[%s %4s %s]  ",
                BBLU, display_attr(my["cps"], ob->query_spi()), NOR );
        
                
             
                line += sprintf("������[%s%12d%s (%s+%4d%s)%s]  �мܣ�[%s%12d%s]%s\n"NOR,
                BBLU HIC, (dodge_points + (weapon ? parry_points: (parry_points/10))) + 1, HIG,
                HIW, ob->query_temp("apply/armor"), HIG, NOR,
                BBLU HIC, parry_points + 1, NOR, NOR);

                line += sprintf( " ɱ����"GRN"["BBLU HIW"%6d"NOR""GRN"]"NOR" ",
                ob->query("MKS")+ob->query("PKS"));

        
                line += sprintf( " ɱ�ˣ�"GRN"["BBLU HIR"%6d"NOR""GRN"]"NOR"  \n\n",
                                                        ob->query("PKS") );
        
                if(ob->query("kill/pkgain") ) { 
          line +=sprintf(" �У˵������ӣ� %s  \n",
       COMBAT_D->chinese_daoxing(ob->query("kill/pkgain")));
          if(!ob->query("kill/pklose") &&
        !ob->query("kill/nkgain") ) line+="\n";
        }
                if(ob->query("kill/pklose") ) {
          line +=sprintf(" �У˵��м��٣� %s\n",
       COMBAT_D->chinese_daoxing(ob->query("kill/pklose")));
          if(!ob->query("kill/nkgain") ) line+="\n";
        }
                if(ob->query("kill/nkgain") ) {
          line +=sprintf(" �Σ˵������ӣ� %s\n\n",
                COMBAT_D->chinese_daoxing(ob->query("kill/nkgain")));
        }

                line += sprintf(" ���о��磺[%s% 6s%s]  ��ѧ���磺[%s%20s%s] \n",
                BBLU HIR, RANK_D->describe_dx(ob->query("daoxing")), NOR,
                BBLU HIG, RANK_D->describe_exp(ob->query("combat_exp")), NOR);
                         
        line += sprintf(" ������Ϊ��[%s%6s%s]  ������Ϊ��[%s%20s%s] \n\n",
                BBLU HIR, RANK_D->describe_fali(ob->query("max_mana")), NOR,
                BBLU HIG, RANK_D->describe_neili(ob->query("max_force")), NOR);
        
                line += sprintf( " "HIY"�ԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡ� �������� �ԡԡԡԡԡԡ�"NOR"\n\n");
         
        write(line+BBLK);
        return 1;
}

string display_attr(int gift, int value)
{
        if( value > gift ) return sprintf( HIY "%4d", value );
        else return sprintf("%3d", value)
string status_color(int current, int max
        int percent
        if( max ) percent = current * 100 / max
        else percent = 100
        if( percent > 100 ) return HIC
        if( percent >= 90 ) return HIG
        if( percent >= 60 ) return HIY
        if( percent >= 30 ) return YEL
        if( percent >= 10 ) return HIR
        return RED
string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor
        string ret
        int i, n, eff_n, max_n = 20
        if( max == 0 ) max = 1
        n = val * 100 / max / 5
        eff_n = eff * 100 / max / 5
        if( n < 0 ) n = 0
        if( eff_n < 0 ) eff_n = 0
        if( n > max_n ) n = max_n
        if( eff_n > max_n ) eff_n = max_n
        ret = NOR "[" + bcolor + fcolor 
        for( i = 0 ; i < max_n; i ++ ) 
                if( i > eff_n ) ret += dcolor
                if( i < n )  ret += "#"
                else ret += "o"
        
        ret += fcolor + NOR "]"
        return ret
int help(object me
        write(@HEL
ָ���ʽ��scor
          score <��������>      ����ʦר�ã
��ʾ�Լ�����ָ�����󣨺�����Ļ������ϡ
���ѶϢ��h
HEL
        )
        return 1
