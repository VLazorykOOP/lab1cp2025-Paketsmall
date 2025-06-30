using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

public class MainForm : Form
{
    private DataGridView dgv;
    private Button btnAdd;
    private Button btnEdit;
    private string connectionString = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=FurnitureDb;Integrated Security=True";

    public MainForm()
    {
        this.Text = "Облік меблів";
        this.Width = 800;
        this.Height = 400;

        dgv = new DataGridView();
        dgv.Top = 0;
        dgv.Left = 0;
        dgv.Width = 770;
        dgv.Height = 300;
        dgv.ReadOnly = true;
        dgv.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
        dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;

        btnAdd = new Button();
        btnAdd.Text = "Додати";
        btnAdd.Top = 310;
        btnAdd.Left = 10;
        btnAdd.Click += BtnAdd_Click;

        btnEdit = new Button();
        btnEdit.Text = "Редагувати";
        btnEdit.Top = 310;
        btnEdit.Left = 110;
        btnEdit.Click += BtnEdit_Click;

        this.Controls.Add(dgv);
        this.Controls.Add(btnAdd);
        this.Controls.Add(btnEdit);

        this.Load += MainForm_Load;
    }

    private void MainForm_Load(object sender, EventArgs e)
    {
        LoadData();
    }

    private void BtnAdd_Click(object sender, EventArgs e)
    {
        AddFurnitureForm form = new AddFurnitureForm(connectionString);
        form.ShowDialog();
        LoadData();
    }

    private void BtnEdit_Click(object sender, EventArgs e)
    {
        if (dgv.CurrentRow == null || dgv.CurrentRow.Index < 0)
        {
            MessageBox.Show("Виберіть рядок для редагування.");
            return;
        }

        Furniture item = new Furniture();
        item.Id = Convert.ToInt32(dgv.CurrentRow.Cells["Id"].Value);
        item.Type = dgv.CurrentRow.Cells["Type"].Value.ToString();
        item.Brand = dgv.CurrentRow.Cells["Brand"].Value.ToString();
        item.Manufacturer = dgv.CurrentRow.Cells["Manufacturer"].Value.ToString();
        item.Supplier = dgv.CurrentRow.Cells["Supplier"].Value.ToString();
        item.Price = Convert.ToDecimal(dgv.CurrentRow.Cells["Price"].Value);

        AddFurnitureForm editForm = new AddFurnitureForm(connectionString, item);
        editForm.ShowDialog();
        LoadData();
    }

    private void LoadData()
    {
        SqlConnection con = new SqlConnection(connectionString);
        SqlDataAdapter adapter = new SqlDataAdapter("SELECT * FROM Furniture", con);
        DataTable dt = new DataTable();
        adapter.Fill(dt);
        dgv.DataSource = dt;
    }
}
