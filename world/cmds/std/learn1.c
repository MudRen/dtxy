// learn.c

#include <skill.h>

inherit F_CLEAN_UP;

string *reject_msg = ({
        "˵������̫�����ˣ�����ô�ҵ���\n",
        "�����ܳ�����һ����˵������̣�����ô�ҵ���\n",
        "Ц��˵��������Ц�ˣ��������С�������ʸ�ָ�㡹��ʲô��\n",
});

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string skill, teacher, master;
        object ob;
        int master_skill, my_skill, sen_cost;
        int time, upper, sen1;
        int amount, qskill, qlearned, i;
	float my_skill_power;
        if(!arg) return notify_fail
                    ("ָ���ʽ��learn <����> from <ĳ��>\n");

        //if(sscanf(arg, "%s for %d", arg, time)!=2 )
            time=1;

        //if(time<1) time=1;
        //if(time>4) time=4;

        if(!arg || sscanf(arg, "%s from %s", skill, teacher)!=2 )
            return notify_fail
                    ("ָ���ʽ��learn <����> from <ĳ��>\n");

        if( me->is_fighting() )
                return notify_fail("����ĥǹ������������\n");

        if(me->is_busy())
            return notify_fail("����æ���ء�\n");

        if( !(ob = present(teacher, environment(me))) || !ob->is_character())
                return notify_fail("��Ҫ��˭��̣�\n");

        if( !living(ob) )
                return notify_fail("�ţ���������Ȱ�" + ob->name() + "Ū����˵��\n");
	if( userp(ob) )
                return notify_fail("���ָ��ܶ����ʹ�á�\n");
        if( !me->is_apprentice_of(ob) && getuid(ob)!=me->query("couple/id")  && !ob->query("skill_public")
                                                           ) {
//              && getuid(ob)!=me->query("bonze/dadangid") ) {

                notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );
                if( (string)me->query("family/family_name") !=
                        (string)ob->query("family/family_name")
                ||      (int)ob->query("family/privs") != -1 ) {
                        if( !(ob->recognize_apprentice(me)) ) return 0;
                } else return 0; // mon add this return 0. 5/6/98
        }

    	if (getuid(ob) == me->query("couple/id") && !userp(ob) )
                return notify_fail("������һ���ʲô��\n");

        if( ob->is_fighting())
                return notify_fail("���ʦ����ʱû��ָ�����书��\n");

        if( !master_skill = ob->query_skill(skill, 1) )
                return notify_fail("���������±����ұ���ѧ�ˡ�\n");

        notify_fail(ob->name() + "��Ը���������ܡ�\n");
        if( ob->prevent_learn(me, skill) )
                return 0;

        my_skill = me->query_skill(skill, 1);

        if( my_skill < 1&& userp(ob) )
                return notify_fail("�㻹���Ȱѻ��������˵��!\n");// xintai 2/5/01


        if( !SKILL_D(skill)->valid_learn(me) ) return 0;
        sen_cost = 100;
        if( !my_skill ) {
                sen_cost *= 2;
                me->set_skill(skill,0);
        }

        upper= (int)me->query("potential")-(int)me->query("learned_points");

        qskill=me->query_skills()[skill]+1;
        qskill*=qskill;
        qlearned=me->query_learned()[skill];
        amount = qskill-qlearned;
        if( amount <= 0 ) amount = qskill;
        amount += me->query_int();
        i = amount/me->query_int()*2;
        qlearned += amount;
        sen1=(int)me->query("sen");

        if( sen_cost > sen1 )
        {
                write("�����̫���ˣ����ʲôҲû��ѧ����\n");
                me->start_busy(1);
                return 1;
        }
        else
        {
        	me->receive_damage("sen", sen_cost);
        }
        if( i > upper )//����������
                return notify_fail("���Ǳ�ܲ����ˡ�\n");

        printf("����%s����йء�%s�������ʡ�\n", ob->name(),
                to_chinese(skill));

	my_skill_power = 0.0 + my_skill;
        my_skill_power = my_skill_power * my_skill_power * my_skill_power / 10;
        if( (string)SKILL_D(skill)->type()=="martial" && my_skill_power > (int)me->query("combat_exp") )
        {
        	printf("Ҳ����ʵս���鲻�������%s�Ļش������޷���ᡣ\n", ob->name() );
	}
	else if( (string)SKILL_D(skill)->type()=="magic" && my_skill_power > (int)me->query("daoxing") )
	{
        	printf("Ҳ���ǵ��в��������%s�Ļش������޷���ᡣ\n", ob->name() );
	}
	else
	{
		me->add("learned_points", i);
                if( my_skill < master_skill )
                {
                	printf("������%s��ָ�����ƺ���Щ�ĵá�\n", ob->name());
                        me->improve_skill(skill, amount);
                }
                else
                {
                	//if( qlearned<me->query_int() )
                        //	message_vision("$N��$n˵������ġ�"+to_chinese(skill)+"���Ѿ�����Ϊʦ�ˣ�����һ���д��д�ɣ�\n",ob,me);
                        printf("%s�����д���һ���%s�����ƺ���������\n",ob->name(),to_chinese(skill));
                        me->improve_skill(skill, amount,(qlearned>4*qskill && !userp(ob)) ?0:1);
                          //can't learn beyond a player master's level.
                     }
                }
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : learn <����> from <ĳ��>

���ָ������������������й�ĳһ�ּ��ܵ��������⣬��Ȼ������̵Ķ�������
����ϵ�����������ߣ����㾭�����ַ�ʽѧϰ�����ļ���Ҳ�����ܸ���������
�̵��ˣ�Ȼ����Ϊ����ѧϰ��ʽ�൱��һ�֡�����Ĵ��С������ѧϰ����˵����Ϥ
һ���¼������ķ�����

ͨ����һ���˸�ѧ��һ���¼����ǲ�����ʲô��������ģ����Ǿ���ʵ���ϵ�Ӧ����
�������⣬��Щ�������ѧϰһ���¼��ܵĹ����Ǻ���Ҫ�ģ������Ǹ�����Ϊ������
�ܻ����Ļ������ܣ�����Ҫ���ɡ��������⩤������⡹�Ĺ��̲��ܵõ��Ϻõ�Ч��
������ǽ����ַ�������Ĺ����á�Ǳ�ܡ��Ĺ����ʾ��һ�����ܹ��Լ�����ĳЩ��
�⣬��ʾ��(��)�н�����������Ǳ�ܣ��������������Ǳ��ʱ�Ϳ����������ָ��
������������̣�����ý�����
(PS. Ǳ�ܻ�������������Ķ��壬����ֻ������֮һ )

����ѧϰҲ��Ҫ����һЩ�����������ĵľ��������Լ�������ѧϰ����������йء�

�������֪�����ܴӶԷ�ѧ��ʲô���ܣ�����Է������ʦ���������� skills ָ��
ֱ�Ӳ鿴������������ʦ������ôͨ��������������ʾ����ֻ���Լ���취��

�������ָ�� : practice��study
HELP
        );
        return 1;
}
