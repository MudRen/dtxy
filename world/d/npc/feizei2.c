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
});

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
                    
        j = random(sizeof(families));
        k = random(sizeof(families));
        newob = new(__DIR__"fei");
        newob->set("target",families[k]);
        newob->invocation( j );
        reset_eval_cost();
        
        switch(families[k])
        {
                case "����ɽ���Ƕ�":
                        m_name="��������(Master puti)";//
                        newob->carry_object("/d/npc/obj/armor");
                        break;
                case "�¹�":
                        m_name="����ĸ(Xi wangmu)";//
                        newob->carry_object("/d/npc/obj/ring");
                        break;
                case "���޵ظ�":
                        m_name="�ز�������(Dizang pusa)";//
                        newob->carry_object("/d/npc/obj/kui");
                        break;
                case "�ݿ�ɽ�޵׶�":
                        m_name="����(Yu shu)";//
                        newob->carry_object("/d/npc/obj/shield");
                        break;
                case "������":
                        m_name="�׷�����(lao ren)";//
                        newob->carry_object("/d/npc/obj/magua");
                           break;
                case "���ƶ�":
                        m_name="�Ʒɻ�(huang feihu)";//
                        newob->carry_object("/d/npc/obj/armor");
                        break;
                case "��ѩɽ":
                        m_name="��������(Dapeng mingwang)";//
                        newob->carry_object("/d/npc/obj/shoes");
                        break;
                case "��ׯ��":
                        m_name="��Ԫ����(Zhenyuan daxian)";
                        newob->carry_object("/d/npc/obj/shield");
                        break;
                case "�Ϻ�����ɽ":
                        m_name="��������(Guanyin pusa)";//
                        newob->carry_object("/d/npc/obj/ring");
                        break;
                case "��������":
                        m_name="����(Ao guang)";//
                        newob->carry_object("/d/npc/obj/armor");
                        break;
                case "��˿��":
                        m_name="��ϼ����(zixia xianzi)";//
                        newob->carry_object("/d/npc/obj/necklace");
                        break;
                case "��ɽ����":
                        m_name="��ɽ��ʥ(jian sheng)";//
                        newob->carry_object("/d/npc/obj/kui");
                        break;
                case "���ƻʹ�":
                        m_name="��̫��(tang taizong)";//
                        newob->carry_object("/d/npc/obj/jing");
                        break;
        }
          message("system",HIG"��"+HIR+"����׷ɱ��"+HIG+"��"+HIW+m_name+HIG"����������������߱�����ɽ֮����"+"�����Ӵ���"+families[j]+"һ��,ɱ���⡣\n"NOR,users());
          remove_call_out("choose_npc");
          call_out("choose_npc",600);
       
}
