// modi by tomcat 

#include <ansi.h>

inherit F_DBASE;

string *families = ({
  "��ѩɽ",
  "����ɽ���Ƕ�",
  "�¹�",
  "�Ϻ�����ɽ",
  "���޵ظ�",
  "��˿��",
  "������",
  "��������",
  "�ݿ�ɽ�޵׶�",
  "��ׯ��",
  "���ƶ�",
  "��ɽ����",
  "���ƻʹ�",
  "�ڼ���",
  "�����",
  "���ù�",
  "Ů����",
  "����",
});

string *feizei=({"fei-putuo","fei-moon","fei-wzg","fei-shushan","fei-hyd",
    "fei-fangcun","fei-hell","fei-jjf","fei-pansi","fei-dragon", "fei-xueshan",
     "fei-wudidong",});

void create()
{
        seteuid(getuid());
        set("name","");
        remove_call_out("choose_npc");
        call_out("choose_npc",2);
}

void choose_npc()
{
        int i, j ,k,ppl;
        object *list, newob;
        string str,m_name;
        string smp;
        smp  = "������ɽ֮��";
                   
        j = random(sizeof(families));
        k = random(sizeof(families));
        newob = new(__DIR__+feizei[random(sizeof(feizei))]);
        newob->set("target",families[k]);
        newob->invocation( j );
        reset_eval_cost();
        
        switch(families[k])
        {
                case "����ɽ���Ƕ�":
                        m_name="��������(Master puti)";//
                        newob->carry_object("/d/npc/obj/stick");
                        break;
                case "�¹�":
                        m_name="����ĸ(Xi wangmu)";//
                        newob->carry_object("/d/npc/obj/whip");
                        break;
                case "���޵ظ�":
                        m_name="�ز�������(Dizang pusa)";//
                        newob->carry_object("/d/npc/obj/whip");
                        break;
                case "�ݿ�ɽ�޵׶�":
                        m_name="����(Yu shu)";//
                        newob->carry_object("/d/npc/obj/blade");
                        break;
                case "������":
                        m_name="�׷�����(lao ren)";//
                        newob->carry_object("/d/npc/obj/axe");
                           break;
                case "���ƶ�":
                        m_name="�Ʒɻ�(huang feihu)";//
                        newob->carry_object("/d/npc/obj/spear");
                        break;
                case "��ѩɽ":
                        m_name="��������(Dapeng mingwang)";//
                        newob->carry_object("/d/npc/obj/qin");
                        break;
                case "��ׯ��":
                        m_name="��Ԫ����(Zhenyuan daxian)";
                        if(random(2)) 
                           newob->carry_object("/d/npc/obj/staff");
                        else
                           newob->carry_object("/d/obj/drug/renshen-guo");
                        break;
                case "�Ϻ�����ɽ":
                        m_name="��������(Guanyin pusa)";//
                        newob->carry_object("/d/npc/obj/staff");
                        break;
                case "��������":
                        m_name="����(Ao guang)";//
                        newob->carry_object("/d/npc/obj/fork");
                        break;
                case "��˿��":
                        m_name="��ϼ����(zixia xianzi)";//
                        newob->carry_object("/d/npc/obj/whip");
                        break;
                case "��ɽ����":
                        m_name="��ɽ��ʥ(jian sheng)";//
                        newob->carry_object("/d/npc/obj/sword");
                        break;
                case "���ƻʹ�":
                        m_name="��̫��(tang taizong)";//
                        newob->carry_object("/d/npc/obj/mace");
                        smp = "���ƹ���";
                        break;
                case  "�ڼ���":
                        m_name="�ڼ�������(wuji guowang)";//
                        newob->carry_object("/d/npc/obj/kui");
                        smp = "�ڼ�������";
                        break;
                case  "�����":
                        m_name="���������(baoxiang guowang)";//
                        newob->carry_object("/d/npc/obj/magua");
                        smp = "���������";
                        break;
                case  "���ù�":
                        m_name="���ù�����(tianzhu guowang)";//
                        newob->carry_object("/d/npc/obj/pifeng");
                        smp = "���ù�����";
                        break;
                case  "Ů����":
                        m_name="Ů��������(nuer guowang)";//
                        newob->carry_object("/d/npc/obj/ring");
                        smp = "Ů��������";
                        break;
                case  "����":
                        m_name="��������(yuhua xianling)";//
                        newob->carry_object("/d/npc/obj/shoes");
                        smp = "���ع���";
                        break;
                        
        }
message("system",HIW"��"+HIR+"���Ƹ�ʾ"+HIW+"��"+HIY+m_name+NOR"�����������������"+smp+"�������Ӵ���"+families[j]+"һ��,ɱ���⡣\n"NOR,users());
remove_call_out("choose_npc");
          call_out("choose_npc",600);
       
}
