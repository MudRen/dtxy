// modi by xintai 2/15/01

#include <ansi.h>

inherit F_DBASE;

string *families = ({
  "��ѩɽ",
  "����ɽ���Ƕ�",
  "����ɽ���鶴",
  "�Ϻ�����ɽ",
  "���޵ظ�",
  "��˿��",
  "������",
  "��������",
  "��ׯ��",
  "�ݿ�ɽ�޵׶�",
  "���ƶ�",
  "����ɢ��",
  "�¹�",
  "��ɽ��",
});

void create()
{
        seteuid(getuid());
        set("name","");
        remove_call_out("choose_mpc");
        call_out("choose_mpc",10);
}

void choose_mpc()
{
        int i, j ,k,ppl;
        object *list, newob;
        string str,m_name;
        list = users();
        i = sizeof(list);

        if (i < 5){
        remove_call_out("choose_mpc");
        call_out("choose_mpc",120);
        return;
        }

        j = random(sizeof(families));
        k = random(sizeof(families));
        while( i-- ) {
                if (!wizardp(list[i]) && list[i]->query("family/family_name") == families[j]
                && (list[i]->query("combat_exp") + list[i]->query("daoxing"))> 10000 )

                {
                newob = new(__DIR__"npc");
                newob->set("target",families[k]);
                if(newob->invocation(list[i], k ))
                ppl++;
                else
                destruct(newob);
                }
        }
        
        reset_eval_cost();
        
        switch(families[k])
        {
                case "����ɽ���Ƕ�":
                        m_name="��������(Master puti)";//
                        break;
                case "����ɽ���鶴":
                        m_name="�����(Guang chengzi)";//
                        break;
                case "���޵ظ�":
                        m_name="�ز�������(Dizang pusa)";//
                        break;
                case "�ݿ�ɽ�޵׶�":
                        m_name="����(Bi shu)";//
                        break;
                case "������":
                        m_name="��ҧ��(Cheng yaojin)";//
                        break;
                case "���ƶ�":
                        m_name="ţħ��(Niu mowang)";//
                        break;
                case "��ѩɽ":
                        m_name="��ȸ����(Kongque gongzhu)";//
                        break;
                case "��ׯ��":
                        m_name="��Ԫ����(Zhenyuan daxian)";
                        break;
                case "�Ϻ�����ɽ":
                        m_name="�Ʋ�ͯ��(Shancai tongzi)";//
                        break;
                case "��������":
                        m_name="����(Ao guang)";//
                        break;
                case "��˿��":
                        m_name="��ϼ����(Zixia xianzi)";//
                        break;
                case "��ɽ��":
                        m_name="����ң(Li xiaoyao)";//
                        break;
                case "����ɢ��":
                        m_name="��ɽ����(Zhongshan fuzi)";//
                       break;
		case "�¹�":
                        m_name="����ĸ(Xi wangmu)";//
                       break;
        }
        if (ppl)
        {
        if (j != k)
        message("system",HIW"��"+HIR+families[k]+HIW+"��"+HIY+m_name+CYN"����"+HIM+chinese_number(ppl)+CYN"��"+HIW+families[j]+CYN"�̿����ڱ������£��ڵ����ٻػ�����\n"NOR,users());
        else
        message("system",HIW"��"+HIR+families[k]+HIW+"��"+HIY+m_name+CYN"������"+HIM+chinese_number(ppl)+CYN"����Т���ӣ���ʦ���棬�ڵ����ٻػ�����\n"NOR,users());
        remove_call_out("choose_mpc");
        call_out("choose_mpc",250);
        }
        else
        {
        message("system",HIG"������ʢ����̫ƽ������������һ��̾�˿�����\n"NOR,users());
        message("system",HIG"������ʢ����̫ƽ����(taiping gongzhu)����������,һ�����,һ���滨!\n"NOR,users());
        remove_call_out("choose_mpc");
        call_out("choose_mpc",60);
        }
}


