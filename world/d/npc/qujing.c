//ȡ��

#include <ansi.h>

inherit F_DBASE;

string *families = ({
  "�ڼ���",
  "�����",
  "���ù�",
  "Ů����",
  "����",
  "��ƽ��",
  "��ׯ��",
  "������",
  "�շ���",
  "�����",
  "���Ϲ�",
  "���ٹ�",
  "���޹�",
  "����ׯ",
  });

void create()
{
        seteuid(getuid());
        set("name","");
        remove_call_out("choose_npc");
        call_out("choose_npc",3);      

}

void choose_npc()
{
        int i, j ,k,ppl;
        object *list, newob;
        string str;
        object ts,swk,zbj,shs;               

        k = random(sizeof(families));        
        ts = new(__DIR__"ts");
        ts->set("target",families[k]);
        ts->invocation(k);
message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��������"+NOR"������! ��˵��������ʦͽ�Ѿ�����"+families[k]+"�ˣ����Ų��þͻᵽ����ɽ�ˡ�\n"NOR,users());
        reset_eval_cost();
        remove_call_out("choose_npc");
        call_out("choose_npc",18000);
}

