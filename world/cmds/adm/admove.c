// by Canoe
// ������Ʒ�ĸ���ʱ����ʧ���
// ֻ�ܸ���testone����
// 2001.07.02
int main(object me, string arg)
{
object who,book;
if( !objectp(book = present(arg, me)) ) 
                        return notify_fail("������û��"+arg+"����������\n");
if(!arg) return notify_fail("��Ҫ��testoneʲô������\n");
if(!who=find_player("testone"))
                return notify_fail("testone����mud�\n");
if(!book->move(who))
                return notify_fail("�ƶ�ʧ�ܡ�\n");
write(arg+"�ɹ��ƶ���testone���ϡ�\n");
return 1;
} 
 
