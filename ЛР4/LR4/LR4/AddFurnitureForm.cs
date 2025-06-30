using System;
using System.Data.SqlClient;
using System.Windows.Forms;

public class AddFurnitureForm : Form
{
    private TextBox[] inputs = new TextBox[5];
    private string connStr;
    private Furniture editItem;

    public AddFurnitureForm(string connectionString, Furniture item = null)
    {
        connStr = connectionString;
        editItem = item;

        this.Text = item == null ? "Додати меблі" : "Редагувати меблі";
        this.Width = 400;
        this.Height = 300;

        string[] labels = { "Вид", "Марка", "Виробник", "Постачальник", "Ціна" };

        for (int i = 0; i < labels.Length; i++)
        {
            Label lbl = new Label();
            lbl.Text = labels[i];
            lbl.Top = 10 + i * 40;
            lbl.Left = 10;
            lbl.Width = 100;

            TextBox txt = new TextBox();
            txt.Top = lbl.Top;
            txt.Left = 120;
            txt.Width = 200;

            inputs[i] = txt;
            this.Controls.Add(lbl);
            this.Controls.Add(txt);
        }

        Button saveButton = new Button();
        saveButton.Text = "Зберегти";
        saveButton.Top = 220;
        saveButton.Left = 120;
        saveButton.Click += SaveData;

        this.Controls.Add(saveButton);

        if (item != null)
        {
            inputs[0].Text = item.Type;
            inputs[1].Text = item.Brand;
            inputs[2].Text = item.Manufacturer;
            inputs[3].Text = item.Supplier;
            inputs[4].Text = item.Price.ToString();
        }
    }

    private void SaveData(object sender, EventArgs e)
    {
        decimal price;
        if (string.IsNullOrWhiteSpace(inputs[0].Text) ||
            string.IsNullOrWhiteSpace(inputs[1].Text) ||
            string.IsNullOrWhiteSpace(inputs[2].Text) ||
            string.IsNullOrWhiteSpace(inputs[3].Text) ||
            !decimal.TryParse(inputs[4].Text, out price))
        {
            MessageBox.Show("Будь ласка, заповніть усі поля коректно.");
            return;
        }

        SqlConnection con = new SqlConnection(connStr);
        con.Open();

        SqlCommand cmd;

        if (editItem == null)
        {
            cmd = new SqlCommand("INSERT INTO Furniture (Type, Brand, Manufacturer, Supplier, Price) VALUES (@t, @b, @m, @s, @p)", con);
        }
        else
        {
            cmd = new SqlCommand("UPDATE Furniture SET Type=@t, Brand=@b, Manufacturer=@m, Supplier=@s, Price=@p WHERE Id=@id", con);
            cmd.Parameters.AddWithValue("@id", editItem.Id);
        }

        cmd.Parameters.AddWithValue("@t", inputs[0].Text);
        cmd.Parameters.AddWithValue("@b", inputs[1].Text);
        cmd.Parameters.AddWithValue("@m", inputs[2].Text);
        cmd.Parameters.AddWithValue("@s", inputs[3].Text);
        cmd.Parameters.AddWithValue("@p", price);
        cmd.ExecuteNonQuery();
        con.Close();

        MessageBox.Show("Збережено!");
        this.Close();
    }
}
