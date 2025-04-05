#include "stdafx.h"

namespace Error
{
    // ����� ������: 0 - 99 - ��������� ������ 
    //				100 - 109 - ������ ���������� 
    //				110 - 119 - ������ �������� � ������ ������
    Error errors[ERROR_MAX_ENTRY]
    {
        ERROR_ENTRY(0, "�������������� ������"),
        ERROR_ENTRY(1, "������ �����"),
        ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
        ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
        ERROR_ENTRY(100, "������ -in ��� ������������� ��������� ������"),
        ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
        ERROR_ENTRY_NODEF(104, "������ ��� ������������� ��������� ������"),
        ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
        ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
        ERROR_ENTRY(110, "������ ��� ������������� ��������� ������ � ������������� ��������� (-in)"),
        ERROR_ENTRY(111, "�������������� ������ � ��������� ������ � ������������� ��������� (-in)"),
        ERROR_ENTRY(112, "������ ��� ������������� ��������� -log"),
        ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
        ERROR_ENTRY(120, "������� ������: �������� ���������� ������ �������"),
        ERROR_ENTRY(121, "��������� ����� ��� ���������� ��� ������������ ��� ����������"),
        ERROR_ENTRY(122, "������� ���������������: �������� ���������� ������ �������"),
        ERROR_ENTRY(123, "����������� ������: �������������� �������"),
        ERROR_ENTRY(124, "����������� ������: ������� ������ ���������� ��������"),
        ERROR_ENTRY(125, "����������� ������: ���������� ��������������"),
        ERROR_ENTRY(126, "����������� ������: ����������� ����������"),
        ERROR_ENTRY(127, "����������� ������: ��������� ����� ���������� ��������"),
        ERROR_ENTRY(128, "�� ������� ������� ���� � ��������� ������ � ���������������"),
        ERROR_ENTRY(129, "����������� ������: ������� ��������� ����� ����� (main)"),
        ERROR_ENTRY(130, "����������� ������: ���������� ��������� ����� declare ��� ���������� ����������"),
        ERROR_ENTRY(131, "������������� ������: �� ���������� ����� �����(main)"),
        ERROR_ENTRY(132, "������������� ������: ���������� �������� ���������"),
        ERROR_ENTRY(133, "������������� ������: ������� �� 0"),
        ERROR_ENTRY(134, "������������� ������: �������������� ����� � ���������"),
        ERROR_ENTRY(135, "C������������ ������: ������������ ����������� � ���������� ���������� �������"),
        ERROR_ENTRY(136, "C������������ ������: �������� ��������� ���������"), ERROR_ENTRY_NODEF(137),ERROR_ENTRY_NODEF(138),ERROR_ENTRY_NODEF(139),
        ERROR_ENTRY_NODEF10(140),
        ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
        ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500), ERROR_ENTRY(600,"�������� ��������� ���������"),
        ERROR_ENTRY(601,"��������� ��������"),
        ERROR_ENTRY(602,"������ � ���������"),
        ERROR_ENTRY(603,"������ � ���������� �������"),
        ERROR_ENTRY(604,"������ � ���������� ���������� �������"), ERROR_ENTRY(605,"������ � ������� ����� � ����(if)"), ERROR_ENTRY_NODEF10(700), ERROR_ENTRY_NODEF10(800), ERROR_ENTRY_NODEF10(900),
    };

    Error geterror(int id) // ������� ��� ��������� ������ �� ��������������
    {
        if (id > 0 && id < ERROR_MAX_ENTRY) // ��������, ��������� �� ID � ���������� ���������
            return errors[id]; // ������� ������ �� ���������� ID
        else
            return errors[0]; // ���������� �������������� ������ �� ���������
    }

    Error geterrorin(int id, int line = -1, int col = -1) // ������� ��� ��������� ������ � ��������� ������ � ������� (�� ��������� -1)
    {
        if (id > 0 && id < ERROR_MAX_ENTRY) { // ��������, ��������� �� ID � ���������� ���������
            errors[id].inext.col = col; // ��������� ������� ��� ������
            errors[id].inext.line = line; // ��������� ������ ��� ������
            return errors[id]; // ������� ������ � ����������� �����������
        }
        else {
            return errors[0]; // ���������� �������������� ������ �� ���������
        }
    }
}
