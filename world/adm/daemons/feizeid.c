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
  "��ɽ��",
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
        seteuid(ROOT_UID);
        set("channel_id", "�ڴ澫��");
        CHANNEL_D->do_channel( this_object(), "sys", "\n��������ϵͳ�Ѿ�������\n"); 
        set("name","");
        remove_call_out("choose_npc");
        call_out("choose_npc",10);
}

void choose_npc()
{
        int i, j ,k,ppl;
        object *list, newob;
        string str,m_name;
        string smp;
        smp  = "��ɽ֮��";
                   
        j = random(sizeof(families));
        k = random(sizeof(families));
        newob = new("/d/npc/"+feizei[random(sizeof(feizei))]);
        newob->set("target",families[k]);
        newob->invocation( j );
        reset_eval_cost();
        
        switch(families[k])
        {
                case "����ɽ���Ƕ�":
                        m_name="��������";//
                        newob->carry_object("/d/npc/obj/stick");
						smp = "������";
                        break;
                case "�¹�":
                        m_name="����ĸ";//
                        newob->carry_object("/d/npc/obj/windyshoes");
                                                smp = "����ѥ";
                        break;
                case "���޵ظ�":
                        m_name="�ز�������";//
                        newob->carry_object("/d/npc/obj/whip2");
						smp = "�һ��";
                        break;
                case "�ݿ�ɽ�޵׶�":
                        m_name="����";//
                        newob->carry_object("/d/npc/obj/blade");
						smp = "����";
                        break;
                case "������":
                        m_name="�׷�����";//
                        newob->carry_object("/d/npc/obj/axe");
						smp = "��";
                           break;
                case "���ƶ�":
                        m_name="�Ʒɻ�";//
                        newob->carry_object("/d/npc/obj/spear");
						smp = "��ħǹ";
                        break;
                case "��ѩɽ":
                        m_name="��������";//
                        newob->carry_object("/d/npc/obj/qin");
						smp = "��ħ��";
                        break;
                case "��ׯ��":
                        m_name="��Ԫ����";
                        newob->carry_object("/d/npc/obj/dragonxiao");
                        smp = "������";
                        break;
                case "�Ϻ�����ɽ":
                        m_name="��������";//
                        newob->carry_object("/d/npc/obj/staff");
						smp = "�߱�����";
                        break;
                case "��������":
                        m_name="��������";//
                        newob->carry_object("/d/npc/obj/fork");
						smp = "��ˮ��";
                        break;
                case "��˿��":
                        m_name="��ϼ����";//
                        newob->carry_object("/d/npc/obj/necklace");
						smp = "Ѫ����";
                        break;
                case "��ɽ��":
                        m_name="��ɽ��ʥ";//
                        newob->carry_object("/d/npc/obj/armor");
						smp = "�ƽ�ս��";
                        break;
                case "���ƻʹ�":
                        m_name="��̫��";//
                        newob->carry_object("/d/npc/obj/mace");
                        smp = "��ħ�";
                        break;
                case  "�ڼ���":
                        m_name="�ڼ�������";//
                        newob->carry_object("/d/npc/obj/kui");
                        smp = "�Ͻ��";
                        break;
                case  "�����":
                        m_name="���������";//
                        newob->carry_object("/d/npc/obj/magua");
                        smp = "�����";
                        break;
                case  "���ù�":
                        m_name="���ù�����";//
                        newob->carry_object("/d/npc/obj/pifeng");
                        smp = "�׺�����";
                        break;
                case  "Ů����":
                        m_name="Ů��������";//
                        newob->carry_object("/d/npc/obj/jing");
                        smp = "����";
                        break;
                case  "����":
                        m_name="��������";//
                        newob->carry_object("/d/npc/obj/shield");
                        smp = "Ǭ����";
                        break;
                        
        }
// message("system",HIW"��"+HIR+"��ͥ�챨"+HIW+"��"+HIY+m_name+NOR"�����������������"+smp+"�������Ӵ���"+families[j]+"һ����\n"NOR,users());

message("system",HIY"��"+NOR+"��ͥͨ����"+HIY+"��"+NOR+"ǧ����"+NOR"����ҹһ���ֵ���"+HIC+m_name+HIW+smp+NOR"��������"+HIM+families[j]+NOR"һ���Ӵܡ�\n"NOR,users());remove_call_out("choose_npc");
          call_out("choose_npc",600);
       
}


