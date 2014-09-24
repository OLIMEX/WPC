using System;
using Gtk;

public partial class MainWindow: Gtk.Window
{	
	private Double width;
	private Double thickness;
	private Double length;
	private Int32  vias;
	private Double plating;
	private Double diameter;
	private Double via_length;

	private const Double rho_foil = 0.017; 		
	private const Double rho_plated = 0.019;

	public MainWindow (): base (Gtk.WindowType.Toplevel)
	{
		Build ();
	}
	
	protected void OnDeleteEvent (object sender, DeleteEventArgs a)
	{
		Application.Quit ();
		a.RetVal = true;
	}

	private Double ToMicrons (String input, ComboBox selector)
	{
		Double value = 0;

		if (Double.TryParse (input, out value)) {
			switch (selector.ActiveText) {
			case "mm":	
				value *= 1000;
				break;
			case "mil": 
				value *= 25.4;
				break;
			case "oz/ft^2": 
				value *= 35;
				break;
			}
			return value;
		}
		else
			return 0;
	}

	private Boolean ValuesValid ()
	{
		Boolean valid = true;

		if (width <= 0) {
			WidthEntry.Text = "Error";
			valid = false;
		}

		if (thickness <= 0) {
			ThicknessEntry.Text = "Error";
			valid = false;
		}

		if (length <= 0) {
			LengthEntry.Text = "Error";
			valid = false;
		}

		if (vias < 0) {
			ViaEntry.Text = "Error";
			valid = false;
		}

		if (vias > 0) {
			if (plating <= 0){
				PlatingEntry.Text = "Error";
				valid = false;
			}

			if (diameter <= 0){
				DrillEntry.Text = "Error";
				valid = false;			
			}
			if (via_length <= 0){
				ViaLengthEntry.Text = "Error";
				valid = false;
			}
		}

		return valid;
	}

	protected void Calculate (object sender, EventArgs e)
	{
		Double resistance = 0;

		// Tracks
		width = ToMicrons (WidthEntry.Text, WidthCombo);
		thickness = ToMicrons (ThicknessEntry.Text, ThicknessCombo);
		length = ToMicrons (LengthEntry.Text, LengthCombo);

		// Vias
		vias = -1;
		if (ViaEntry.Text != "") {
			if (Int32.TryParse (ViaEntry.Text, out vias)) {
				plating = ToMicrons (PlatingEntry.Text, PlatingCombo);
				diameter = ToMicrons (DrillEntry.Text, DrillCombo);
				via_length = ToMicrons (ViaLengthEntry.Text, ViaLengthCombo);
			}
		} else
			vias = 0;

		// Calculate and display resistance
		if (ValuesValid ()) {
			resistance = rho_foil * length / (width * thickness);
			if (vias > 0){
				Double radius = diameter / 2.0;
				Double area = (Math.PI * Math.Pow(radius,2.0)) - (Math.PI * Math.Pow(radius-plating, 2.0));
				resistance += vias * rho_plated * via_length / area;
			}
			ResistanceLabel.Text = String.Format ("Resistance = {0:G4} Ω", resistance);
		}
		else
			ResistanceLabel.Text = "Error";
	}

}
